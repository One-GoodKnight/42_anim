#include "game/game.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "window/rendering/init_ui.h"
#include "window/input.h"
#include "window/window.h"
#include "window/rendering/ui.h"
#include "init.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

static int	load_assets(Font *font, Texture2D *logo_texture)
{
	Image	logo_img;

	*font = init_font();
	if (!font->glyphs)
		return (-1);

	logo_img = LoadImage("assets/42_Logo.png");
	if (!logo_img.data)
	{
		UnloadFont(*font);
		return (-1);
	}

	ImageColorInvert(&logo_img);
	*logo_texture = LoadTextureFromImage(logo_img);
	UnloadImage(logo_img);

	return (0);
}

static int	release(Font *font, Texture2D *logo, t_vec *messages, int ret)
{
	vec_clear(messages);

	UnloadFont(*font);
	UnloadTexture(*logo);

	CloseWindow();
	return (ret);
}

int	game_loop(t_net *net, t_qst *qst, t_game *game)
{
	Font		font;
	Texture2D	logo;

	init_window();

	if (load_assets(&font, &logo) == -1)
		return (-1);

	t_input input;
	init_input(&input);

	t_ui ui;
	init_ui(&ui);

	while (game->state == IN_GAME)
	{
		if (read_all_messages(net->sock, &net->messages) == -1)
			return (release(&font, &logo, &net->messages, -1));
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

		render_ui(&ui, qst, &input, font, logo);
	}

	while (game->state == RESULTS)
	{
		// todo: display winner
		printf("%s\n", game->winner_name);
		game->state = FINNISHED;
	}

	return (release(&font, &logo, &net->messages, 0));
}
