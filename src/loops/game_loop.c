#include "game/game.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "window/input.h"
#include "window/window.h"
#include "window/rendering/ui.h"
#include "init.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

static int	release(Font *font, t_vec *messages, int ret)
{
	vec_clear(messages);
	UnloadFont(*font);
	CloseWindow();
	return (ret);
}

int	game_loop(t_net *net, t_qst *qst, t_game *game)
{
	init_window();
	Font font = init_font();

	t_input input;
	init_input(&input);

	while (game->state == IN_GAME)
	{
		if (read_all_messages(net->sock, &net->messages) == -1)
			return release(&font, &net->messages, -1);
		handle_conflicts(net);

		if (net->state == HOST)
		{
			announce_hosting(net);
			process_msg_host(net, qst);
		}

		// todo: become a host if the host left
		process_msg_client(net, game, qst);

		vec_clear(&net->messages);

		handle_input(&input);
		if (IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
			send_answer(net->sock, net->host_addr, (char *)input.text);
		render_ui(qst, &input, font);
	}

	while (game->state == RESULTS)
	{
		// todo: display winner
		printf("%s\n", game->winner_name);
		game->state = FINNISHED;
	}

	return (release(&font, &net->messages, 0));
}
