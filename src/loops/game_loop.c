#include "game/game.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "ui/render_ui/render_ui.h"
#include "ui/update_ui/pid_controller.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "window/input.h"
#include "window/window.h"
#include "init.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

static int	load_assets(Font *font, Font *font_anim, Texture2D *logo_texture)
{
	Image	logo_img;

	*font = init_font("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE);
	if (!font->glyphs)
		return (-1);

	*font_anim = init_font("assets/Motorblock.ttf", FONT_SIZE_ANIM_TEXT);
	if (!font_anim->glyphs)
	{
		UnloadFont(*font);
		return (-1);
	}

	logo_img = LoadImage("assets/42_Logo.png");
	if (!logo_img.data)
	{
		UnloadFont(*font);
		UnloadFont(*font_anim);
		return (-1);
	}

	ImageColorInvert(&logo_img);
	*logo_texture = LoadTextureFromImage(logo_img);
	UnloadImage(logo_img);

	return (0);
}

static int	release(Font *font, Font *font_anim, Texture2D *logo, t_vec *messages, int ret)
{
	vec_clear(messages);

	UnloadFont(*font);
	UnloadFont(*font_anim);
	UnloadTexture(*logo);

	CloseWindow();
	return (ret);
}

int	game_loop(t_net *net, t_qst *qst, t_game *game)
{
	Font				font;
	Font				font_anim;
	Texture2D			logo;
	t_input				input;
	t_ui				ui;
	t_pid_controller	pid_controller;

	init_window();

	if (load_assets(&font, &font_anim, &logo) == -1)
		return (-1);

	init_input(&input);
	init_ui(&ui);
	init_pid_controller(&pid_controller);

	while (game->state != FINNISHED)
	{
		if (IsKeyPressed(KEY_ESCAPE))
			return (release(&font, &font_anim, &logo, &net->messages, 0));

		if (read_all_messages(net->sock, &net->messages) == -1)
			return (release(&font, &font_anim, &logo, &net->messages, -1));
		handle_conflicts(net);

		if (net->state == HOST)
		{
			announce_hosting(net);
			process_msg_host(net, qst);
		}

		// todo: become a host if the host left
		process_msg_client(net, game);

		vec_clear(&net->messages);

		handle_input(&input);

		if (IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
			send_answer(net->sock, net->host_addr, (char *)input.text);

		if (game->state == RESULTS)
		{
			ui.result_screen_time_left -= ui.dt;
			if (ui.result_screen_time_left <= 0)
				game->state = FINNISHED;
		}

		update_ui(&ui, &pid_controller);
		render_ui(&ui, (char *)game->question, &input, font, font_anim, logo);
	}

	return (release(&font, &font_anim, &logo, &net->messages, 0));
}
