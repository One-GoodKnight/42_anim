#include "game/game.h"
#include "net/network.h"
#include <stdio.h>

void	check_host_timeout(t_net *net, t_game *game)
{
	if (game && time(NULL) - net->last_heartbeat_received >= HOST_TIMEOUT)
		game->state = FINISHED;
}
