#include "raylib.h"
#include "window.h"
#include "focus.h"
#include "data.h"
#include "read_file.h"
#include "input.h"
#include "ui.h"
#include "question.h"
#include "won.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int	main(void)
{
	//start_focus_thread(WINDOW_TITLE);
	
	srand(time(NULL));

	t_data	data;
	get_lines_from_file(&data);
	if (!data.lines)
		return (1);

	t_input input;
	init_input(&input);

	t_qst	qst;
	init_question(&qst, &data);
	if (!qst.data.qst.text)
		return (1);

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

	free(qst.data.qst.text);
	free(qst.data.qst.utf8);
	free_array((void *)data.lines);
	UnloadFont(font);
	return (0);
}
