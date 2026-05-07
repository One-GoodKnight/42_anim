#include "game/game.h"
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

static void	process_question(t_net *net, t_msg *msg, t_game *game)
{
	(void)net;
	if (strncmp(msg->msg, "QUESTION:", strlen("QUESTION:")) != 0)
		return ;

	int prefix_len = strlen("QUESTION:");
	strcpy(game->question, msg->msg + prefix_len);

	game->state = IN_GAME;
	printf("Received a question\n");
}

void	process_msg_client(t_net *net, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_hosting(net, msg);
		process_question(net, msg, game);
	}
}
