#include "game/game.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "net/state.h"
#include "ui/render_ui/render_ui.h"
#include "ui/update_ui/pid_controller.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "window/input.h"
#include "window/window.h"
#include "loops.h"
#include "raylib.h"
#include <string.h>

static int	release_window(t_ui *ui, t_vec *messages, int ret)
{
	vec_clear(messages);

	release_ui(ui);

	CloseWindow();
	return (ret);
}

static int handle_network(t_net *net, t_ui *ui, t_qst *qst, t_game *game, t_input *input)
{
	if (read_all_messages(net->sock, &net->messages) == -1)
		return (-1);
	handle_conflicts(net);
	check_host_timeout(net, game);

	if (net->state == HOST)
		host_loop_helper(net, qst, ui->dt);

	process_msg_client(net, game);
	process_msg_client_ui(net, ui, game, input);

	vec_clear(&net->messages);

	return (0);
}

static void	tick_result_screen(t_ui *ui, t_game *game)
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
		return (release_window(&ui, &net->messages, -1));

	init_train(&ui);

	while (game->state != FINISHED)
	{
		if (WindowShouldClose())
			return (release_window(&ui, &net->messages, 0));

		if (handle_network(net, &ui, qst, game, &input) == -1)
			return (release_window(&ui, &net->messages, -1));

		if (net->state == CLIENT)
			send_playing(net);

		handle_input(&input);

		if (ui.state == COMPLETE && IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
			send_answer(net->sock, net->host_addr, (char *)input.text);

		tick_result_screen(&ui, game);

		char *qst = (char *)game->question;
		update_ui(&ui, &pid, qst);
		render_ui(&ui, qst, &input);
	}

	return (release_window(&ui, &net->messages, 0));
}
