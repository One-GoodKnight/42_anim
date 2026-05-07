#include "raylib.h"
#include "file_op/read_file.h"
#include <time.h>
#include <stdlib.h>

void	set_random_seed(void)
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand(ts.tv_sec ^ ts.tv_nsec);
}

int	load_data(t_data *data)
{
	get_lines_from_file(data);
	if (!data->lines)
		return (-1);
	return (0);
}

Font	init_font(char *path, int size)
{
	SetTraceLogLevel(LOG_ERROR);
	Font font = LoadFontEx(path, size, NULL, 255);
	SetTraceLogLevel(LOG_WARNING);
	return font;
}
