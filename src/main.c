#include "raylib.h"
#include "window.h"
#include "focus.h"
#include "input.h"
#include "ui.h"
#include "question.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int	main(void)
{
	//start_focus_thread(WINDOW_TITLE);
	
	srand(time(NULL));

	t_input input;
	init_input(&input);

	t_qst	*qst = generate_question();
	if (!qst)
		return (1);

	init_window();
	Font font = LoadFontEx("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE, NULL, 350);

	while (!WindowShouldClose())
	{
		handle_input(&input);
		render_ui(qst, &input, font);
	}

	CloseWindow();
	return (0);
}
