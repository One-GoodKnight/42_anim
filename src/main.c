#include "raylib.h"
#include "file_op/data.h"
#include "window/input.h"
#include "window/window.h"
#include "window/rendering/ui.h"
#include "game/game.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "net/network.h"
#include "net/state.h"
#include "utils/utils.h"
#include "init.h"
#include "loops.h"
#include "vector.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int release_mem(t_data *data, t_net *net, t_qst *qst, Font *font, int ret)
{
	free_array((void *)data->lines);
	free_qst(qst);
	clean_net(net);

	// raylib
	if (!font)
		return (ret);
	UnloadFont(*font);
	CloseWindow();
	return (ret);
}

int	main(void)
{
	t_data	data;
	t_net	net = {0};
	t_qst	qst = {0};
	t_game	game = {0};

	set_random_seed();

	if (load_data(&data) == -1)
		return (1);
	if (init_net(&net) == -1)
		return release_mem(&data, NULL, NULL, NULL, 1);

	while (1)
	{
		// waiting for a game to start
		if (lobby_loop(&data, &net, &qst, &game) == -1)
			return (1);

		// in the game (window open)
		//if (game_loop() == -1)
		//	return (1);

		init_window();
		Font font = init_font();
		t_input input;
		init_input(&input);

		while (!WindowShouldClose())
		{
			if (read_all_messages(net.sock, &net.messages) == -1)
				return release_mem(&data, &net, &qst, &font, 1);
			handle_conflicts(&net);

			if (net.state == HOST)
			{
				announce_hosting(&net);
				process_msg_host(&net, &qst);
			}

			// todo: become a host if the host left
			process_msg_client(&net, &game, &qst);

			vec_clear(&net.messages);

			handle_input(&input);
			if (IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
				send_answer(net.sock, net.host_addr, (char *)input.text);
			render_ui(&qst, &input, font);
		}


		UnloadFont(font);
		CloseWindow();
	}

	release_mem(&data, &net, &qst, NULL, 0);
}
