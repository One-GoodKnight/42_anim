#include "window.h"
#include "raylib.h"

void	place_window(void)
{
	const int monitorWidth = GetMonitorWidth(0);
	const int monitorHeight = GetMonitorHeight(0);
	SetWindowPosition(monitorWidth / 2 - WINDOW_WIDTH / 2, monitorHeight - WINDOW_HEIGHT);
}

void	init_window(void)
{
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
	place_window();
    SetTargetFPS(60);
}
