#include "file_op/data.h"
#include "game/game.h"
#include "game/question.h"
#include "net/network.h"
#include "net/process_msg.h"
#include "net/actions.h"

int	lobby_loop(t_data *data, t_net *net, t_qst *qst, t_game *game)
{
	while (game->state == WAITING)
	{
		if (net->state == HOST)
		{
			init_question(qst, data);
			if (!qst->data.qst.text)
				return (-1);
			announce_question(net, (char *)qst->data.qst.utf8);
		}

		// both limit the framerate of the loop and wait for the question so game state changes to IN_GAME
		usleep(0.016 * 1000000);

		if (read_all_messages(net->sock, &net->messages) == -1)
			return (-1);

		process_msg_client(net, game, qst);

		vec_clear(&net->messages);
	}

	return (0);
}
