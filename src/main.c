#include "raylib.h"
#include "file_op/data.h"
#include "game/game.h"
#include "game/question.h"
#include "net/network.h"
#include "net/state.h"
#include "utils/utils.h"
#include "init.h"
#include "loops.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

static int release_mem(t_data *data, t_net *net, t_qst *qst, int ret)
{
	free_array((void *)data->lines);
	free_qst(qst);
	clean_net(net);

	return (ret);
}

int	main(void)
{
	t_data	data;
	t_net	net = {0};
	t_qst	qst = {0};
	t_game	game;

	set_random_seed();

	if (load_data(&data) == -1)
		return (1);
	if (init_net(&net) == -1)
		return release_mem(&data, NULL, NULL, 1);
	init_game(&game);

	while (1)
	{
		reset_net_game_state(&net);

		// waiting for a game to start
		if (lobby_loop(&data, &net, &qst, &game) == -1)
			return (1);

		// in the game (window open)
		if (game_loop(&net, &qst, &game) == -1)
			return (1);
	}

	release_mem(&data, &net, &qst, 0);
}
