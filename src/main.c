#include "raylib.h"
#include "window/window.h"
#include "window/focus.h"
#include "file_op/data.h"
#include "file_op/read_file.h"
#include "window/input.h"
#include "window/rendering/ui.h"
#include "logic/question.h"
#include "logic/won.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int	main(void)
{
	//start_focus_thread(WINDOW_TITLE);
	
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	int ttl = 1;
	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));

	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(7474);
	inet_pton(AF_INET, "239.0.0.1", &dest.sin_addr);

	while (1)
	{
		sendto(sock, "Coucou", 7, 0, (struct sockaddr*)&dest, sizeof(dest));
		sleep(1);
	}
	return (0);
	
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

	CloseWindow();

	free_qst(&qst);
	free_array((void *)data.lines);
	UnloadFont(font);
	return (0);
}
