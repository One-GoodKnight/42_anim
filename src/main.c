#include "raylib.h"
#include "window.h"
#include "focus.h"
#include "input.h"
#include "ui.h"
#include <stdio.h>
#include <stdbool.h>

int	main(void)
{
	init_window();
	//start_focus_thread(WINDOW_TITLE);
	
	Font font = LoadFontEx("assets/FiraMono-Regular.ttf", FONT_SIZE, 0, 250);

	t_input input;
	init_input(&input);

	while (!WindowShouldClose())
	{
		handle_input(&input);
		render_ui(&input, font);
	}

	CloseWindow();
	return 0;
}
