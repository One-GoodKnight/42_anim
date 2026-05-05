#include "raylib.h"
#include "window/rendering/ui.h"
#include <time.h>
#include <stdlib.h>

void	set_random_seed(void)
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand(ts.tv_sec ^ ts.tv_nsec);
}

Font	init_font(void)
{
	SetTraceLogLevel(LOG_ERROR);
	Font font = LoadFontEx("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE, NULL, 255);
	SetTraceLogLevel(LOG_WARNING);
	return font;
}
