#include "game/game.h"
#include "net/message.h"
#include "net/network.h"
#include "net/state.h"
#include "string.h"
#include <stdio.h>

void	handle_conflicts(t_net *net, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		if (strncmp(msg->msg, "HOSTING", strlen("HOSTING")) != 0)
			continue ;

		if (msg->sender.sin_addr.s_addr < net->my_addr.s_addr)
		{
			if (net->state == CLIENT && msg->sender.sin_addr.s_addr > net->host_addr.sin_addr.s_addr)
				continue ;

			net->host_addr = msg->sender;
			net->host_addr.sin_port = htons(PORT);
			net->state = CLIENT;
			net->last_heartbeat_received = time(NULL);
		}
	}

	// terminate window if no host
	if (time(NULL) - net->last_heartbeat_received >= HOST_TIMEOUT)
	{
		game->state = FINISHED;
		printf("%lu\n", time(NULL) - net->last_heartbeat_received);
	}
}
