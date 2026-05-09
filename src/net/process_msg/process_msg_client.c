#include "game/game.h"
#include "net/message.h"
#include "net/network.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

static void	process_next_game_cd(t_net *net, t_msg *msg)
{
	if (net->state == HOST)
		return ;

	if (strncmp(msg->msg, "NEXT_GAME_CD:", strlen("NEXT_GAME_CD:")) != 0)
		return ;

	int	prefix_length = strlen("NEXT_GAME_CD:");
	net->next_game_cooldown = atof(msg->msg + prefix_length);
}

void	process_msg_client(t_net *net, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_hosting(net, msg);
		process_start(net, msg, game);
		process_next_game_cd(net, msg);
	}
}
