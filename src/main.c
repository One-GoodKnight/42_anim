#include "window/focus.h"
#include "file_op/data.h"
#include "file_op/read_file.h"
#include "window/input.h"
#include "window/window.h"
#include "window/rendering/ui.h"
#include "logic/question.h"
#include "logic/won.h"
#include "net/actions.h"
#include "net/handle_msg.h"
#include "net/network.h"
#include "net/setup_sock_addr.h"
#include "net/state.h"
#include "utils/utils.h"
#include "vector.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	t_net net = {0};
	if (setup_net(&net) == -1)
		return (1);

	while (1)
	{
		if (read_all_messages(net.sock, &net.messages) == -1)
		{
			clean_net(&net);
			return (1);
		}
		handle_conflicts(&net);

		if (net.state == HOST)
		{
			handle_msg_host(&net);
			announce_hosting(net.sock, net.multicast_addr);
		}
		if (net.state == CLIENT)
		{
			printf("I am a client\n");
			send_answer(net.sock, net.host_addr, "AAA");
			send_answer(net.sock, net.host_addr, "BB");
			send_answer(net.sock, net.host_addr, "CCCCC");
		}
		vec_clear(&net.messages);
		usleep(0.016 * 1000000);
	}

	clean_net(&net);
	return (0);
	
	//start_focus_thread(WINDOW_TITLE);
	
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand(ts.tv_sec ^ ts.tv_nsec);

	t_data	data;
	get_lines_from_file(&data);
	if (!data.lines)
		return (1);

	t_input input;
	init_input(&input);

	t_qst	qst;
	init_question(&qst, &data);
	if (!qst.data.qst.text)
	{
		free_array((void *)data.lines);
		return (1);
	}

	init_window();
	SetTraceLogLevel(LOG_ERROR);
	Font font = LoadFontEx("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE, NULL, 255);
	SetTraceLogLevel(LOG_WARNING);

	while (!WindowShouldClose() && !won(&input, &qst))
	{
		handle_input(&input);
		render_ui(&qst, &input, font);
	}

	UnloadFont(font);
	CloseWindow();

	free_qst(&qst);
	free_array((void *)data.lines);
	return (0);
}
