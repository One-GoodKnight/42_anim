#include "raylib.h"
#include "window.h"
#include "focus.h"
#include "input.h"
#include "ui.h"
#include "question.h"
#include "won.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int	main(void)
{
	//start_focus_thread(WINDOW_TITLE);
	
	srand(time(NULL));

	//unsigned char	**lines = get_lines_from_file();

	t_input input;
	init_input(&input);

	t_qst	qst;
	init_question(&qst);
	if (!qst.data.qst.text)
		return (1);

	init_window();
	Font font = LoadFontEx("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE, NULL, 350);

	while (!WindowShouldClose() && !won(&input, &qst))
	{
		handle_input(&input);
		render_ui(&qst, &input, font);
	}

	CloseWindow();
	return (0);
}
