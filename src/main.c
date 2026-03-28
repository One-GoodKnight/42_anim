#include "raylib.h"
#include "focus.h"
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "Anim"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 250
#define NAVY (Color){0, 0, 64, 255}
#define LIGHT_NAVY (Color){0, 128, 255, 255}

typedef struct s_line
{
	int width;
	int height;
	Color color;
	int trail;
}	t_line;

void	init_line(t_line *line, int width, int height, Color color, int trail)
{
	line->width = width;
	line->height = height;
	line->color = color;
	line->trail = trail;
}

void	place_window(void)
{
	const int monitorWidth = GetMonitorWidth(0);
	const int monitorHeight = GetMonitorHeight(0);
	SetWindowPosition(monitorWidth / 2 - WINDOW_WIDTH / 2, monitorHeight - WINDOW_HEIGHT);
}

void	init(void)
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
	place_window();
    SetTargetFPS(60);
}

void	draw_line(int x, int y, t_line line)
{
	DrawRectangle(x, y, line.width, line.height, line.color);
	if (!line.trail)
		return ;
	for (int i = 0; i < line.trail; i++){
		Color transparent_color = line.color;
		transparent_color.a = 255 - (int)(((float)i / (float)line.trail) * 255);
		DrawRectangle(x + line.width + i, y, 1, line.height, transparent_color);
	}
}

void	draw_box(int x, int y, t_line line, int height, Color color, bool fade)
{
	t_line middle_line = line;
	middle_line.width -= line.height * 2;
	if (fade)
		middle_line.width *= 0.8;
	middle_line.height = height;
	middle_line.color = color;

	t_line vertical_line = line;
	vertical_line.height = height;
	vertical_line.width = line.height;
	vertical_line.trail = 0;

	draw_line(x - line.height, y - line.height, line);
	draw_line(x - line.height, y + height, line);
	draw_line(x - vertical_line.width, y, vertical_line);
	if (!fade)
		draw_line(x - vertical_line.width * 2 + line.width, y, vertical_line);

	draw_line(x, y, middle_line);
}

int	main(void)
{
	init();
	//start_focus_thread(WINDOW_TITLE);

	char text[128] = {0};
	int letterCount = 0;

	while (!WindowShouldClose())
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if (letterCount < 127)
			{
				text[letterCount] = (char)key;
				letterCount++;
				text[letterCount] = '\0';
			}
			key = GetCharPressed();
		}
		BeginDrawing();
		ClearBackground(BLANK);
		//DrawText("It works!", 350, 200, 20, DARKGRAY);
		//DrawText(text, 20, 60, 30, BLUE);

		//target
		t_line target_line;
		init_line(&target_line, 550, 4, PURPLE, 0);
		draw_box(10, 10, target_line, 50, VIOLET, false);

		//input_field
		t_line input_field_line;
		init_line(&input_field_line, 550, 4, LIGHT_NAVY, 100);
		draw_box(100, 120, input_field_line, 50, NAVY, true);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
