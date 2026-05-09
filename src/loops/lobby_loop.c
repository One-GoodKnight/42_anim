#include "file_op/data.h"
#include "game/game.h"
#include "game/question.h"
#include "net/network.h"
#include "net/process_msg.h"
#include "net/actions.h"

static int	tick_next_game(t_data *data, t_net *net, t_qst *qst)
{
	net->next_game_cooldown -= 0.016f;
	if (net->next_game_cooldown > 0)
		return (0);

	init_question(qst, data);
	if (!qst->data.qst.text)
		return (-1);
	announce_start(net);

	return (0);
}

int	lobby_loop(t_data *data, t_net *net, t_qst *qst, t_game *game)
{
	game->state = WAITING;

	while (game->state == WAITING)
	{
		if (time(NULL) - net->last_heartbeat_received >= HOST_TIMEOUT)
			set_to_host(net);

		if (net->state == HOST)
		{
			announce_hosting(net);
			if (tick_next_game(data, net, qst) == -1)
				return (-1);
		}

		// both limit the framerate of the loop and wait for the start packet so game state changes to IN_GAME
		usleep(0.016f * 1000000);

		if (read_all_messages(net->sock, &net->messages) == -1)
			return (-1);

		process_msg_client(net, game);

		vec_clear(&net->messages);
	}

	return (0);
}
