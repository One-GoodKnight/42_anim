#include "window/window.h"
#include "raylib.h"

void	init_window(void)
{
	SetTraceLogLevel(LOG_WARNING);

	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);

	// dummy size of 1x1, if we put 0x0 transparency does not get applied
	InitWindow(1, 1, WINDOW_TITLE);

	int monitor = GetCurrentMonitor();
    int width   = GetMonitorWidth(monitor);
    int height  = GetMonitorHeight(monitor);

	SetWindowSize(width, height);
    SetWindowPosition(0, 0);

    SetTargetFPS(60);
}

