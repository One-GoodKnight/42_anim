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
#include "raylib.h"
#include <string.h>

static int	release_window(t_ui *ui, t_vec *messages, int ret)
{
	vec_clear(messages);

	release_ui(ui);

	CloseWindow();
	return (ret);
}

static int handle_network(t_net *net, t_ui *ui, t_qst *qst, t_game *game)
{
	if (read_all_messages(net->sock, &net->messages) == -1)
		return (-1);
	handle_conflicts(net);

	if (net->state == HOST)
	{
		announce_hosting(net);
		process_msg_host(net, qst);
	}

	// todo: become a host if the host left
	process_msg_client(net, game);
	process_msg_client_ui(net, ui, game);

	vec_clear(&net->messages);

	return (0);
}

static void	handle_result(t_ui *ui, t_game *game)
{
	if (game->state == RESULTS)
	{
		ui->result_screen_time_left -= ui->dt;
		if (ui->result_screen_time_left <= 0)
			game->state = FINISHED;
	}
}

int	game_loop(t_net *net, t_qst *qst, t_game *game)
{
	t_ui				ui;
	t_input				input;
	t_pid_controller	pid;

	init_window();
	init_ui(&ui);
	init_input(&input);
	init_pid_controller(&pid);

	if (load_assets(&ui) == -1)
		return (release_ui(&ui));

	while (game->state != FINISHED)
	{
		if (IsKeyPressed(KEY_ESCAPE))
			return (release_window(&ui, &net->messages, 0));

		if (handle_network(net, &ui, qst, game) == -1)
			return (release_window(&ui, &net->messages, -1));

		handle_input(&input);

		if (ui.state == COMPLETE && IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
			send_answer(net->sock, net->host_addr, (char *)input.text);

		handle_result(&ui, game);

		update_ui(&ui, &pid);
		render_ui(&ui, (char *)game->question, &input);
	}

	return (release_window(&ui, &net->messages, 0));
}
