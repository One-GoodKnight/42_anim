#include "game/game.h"
#include "game/question.h"
#include "net/message.h"
#include "net/network.h"
#include <string.h>
#include <stdio.h>

static void	process_hosting(t_net *net, t_msg *msg)
{
	(void)net;
	if (strncmp(msg->msg, "HOSTING", strlen("HOSTING")) != 0)
		return ;

	printf("Received host heartbeat\n");
}

static void	process_question(t_net *net, t_msg *msg, t_game *game, t_qst *qst)
{
	(void)net;
	if (strncmp(msg->msg, "QUESTION:", strlen("QUESTION:")) != 0)
		return ;

	int prefix_len = strlen("QUESTION:");
	qst->data.qst.utf8 = (unsigned char *)strdup(msg->msg + prefix_len);
	if (!qst->data.qst.utf8)
		return ;

	game->state = IN_GAME;
	printf("Received a question\n");
}

static void	process_winner(t_net *net, t_msg *msg)
{
	(void)net;
	if (strncmp(msg->msg, "WINNER:", strlen("WINNER:")) != 0)
		return ;

	printf("%s\n", msg->msg);
}

void	process_msg_client(t_net *net, t_game *game, t_qst *qst)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_hosting(net, msg);
		process_question(net, msg, game, qst);
		process_winner(net, msg);
	}
}
