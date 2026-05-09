#include "game/game.h"
#include "net/message.h"
#include "net/network.h"
#include <string.h>
#include <stdio.h>

static void	process_hosting(t_net *net, t_msg *msg)
{
	if (strncmp(msg->msg, "HOSTING", strlen("HOSTING")) != 0)
		return ;

	net->last_heartbeat_received = time(NULL);
	printf("Received host heartbeat\n");
}

static void	process_start(t_net *net, t_msg *msg, t_game *game)
{
	if (strncmp(msg->msg, "STARTING", strlen("STARTING")) != 0)
		return ;

	game->state = IN_GAME;
	net->last_heartbeat_received = time(NULL);
	printf("Received start announcement\n");
}

void	process_msg_client(t_net *net, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_hosting(net, msg);
		process_start(net, msg, game);
	}
}
