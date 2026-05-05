#include "window/focus.h"
#include "file_op/data.h"
#include "file_op/read_file.h"
#include "window/input.h"
#include "window/window.h"
#include "window/rendering/ui.h"
#include "game/question.h"
#include "net/actions.h"
#include "net/process_msg.h"
#include "net/network.h"
#include "net/state.h"
#include "utils/utils.h"
#include "init.h"
#include "vector.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

static int release_mem(t_data *data, t_qst *qst, t_net *net, Font *font, int ret)
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
	//start_focus_thread(WINDOW_TITLE);

	set_random_seed();

	t_input input;
	init_input(&input);

	t_data	data;
	get_lines_from_file(&data);
	if (!data.lines)
		return (1);

	t_qst	qst = {0};
	// todo: only initialize a question on host initialization
	init_question(&qst, &data);
	if (!qst.data.qst.text)
		release_mem(&data, NULL, NULL, NULL, 1);

	t_net net = {0};
	if (setup_net(&net) == -1)
		release_mem(&data, &qst, NULL, NULL, 1);

	init_window();
	Font font = init_font();

	while (!WindowShouldClose())
	{
		if (read_all_messages(net.sock, &net.messages) == -1)
			return release_mem(&data, &qst, &net, &font, 1);
		handle_conflicts(&net);

		if (net.state == HOST)
		{
			announce_hosting(&net);
			process_msg_host(&net, &qst);
		}

		// todo: become a host if the host left
		process_msg_client(&net);

		vec_clear(&net.messages);

		handle_input(&input);
		if (IsKeyPressed(KEY_ENTER) && strlen((char *)input.text) > 0)
			send_answer(net.sock, net.host_addr, (char *)input.text);
		render_ui(&qst, &input, font);
	}

	release_mem(&data, &qst, &net, &font, 0);
}
