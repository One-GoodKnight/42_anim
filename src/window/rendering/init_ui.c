#include "window/rendering/corner.h"
#include "window/rendering/ui.h"
#include <stdlib.h>

static void	init_corner(t_corner *corner, int x, int y, t_dir line_one_dir, int line_one_length, t_dir line_two_dir, int line_two_length)
{
	corner->org_x = x;
	corner->org_y = y;

	corner->thickness = BORDER_THICKNESS;

	corner->line_one_dir = line_one_dir;
	corner->line_one_length = line_one_length;

	corner->line_two_dir = line_two_dir;
	corner->line_two_length = line_two_length;

	corner->x_offset = 0;
	corner->y_offset = 0;

	float	t = (float)rand() / (float)RAND_MAX;
	corner->phase = PI * 2 * t;
}

void	init_ui(t_ui *ui)
{
	int monitor = GetCurrentMonitor();
    int width   = GetMonitorWidth(monitor);
    int height  = GetMonitorHeight(monitor);

	ui->width = width;
	ui->height = height;

	ui->dt = 0;

	ui->state = BACKGROUND_FADE;

	ui->fade_progress = 0;

	int	center_x = width / 2;
	int	center_y = height / 2;

	int offset_x = BOX_WIDTH / 2;
	int offset_y = BOX_HEIGHT / 2;

	init_corner(&ui->top_left_corner, center_x - offset_x, center_y - offset_y, SOUTH, 125, EAST, 250);
	init_corner(&ui->top_right_corner, center_x + offset_x, center_y - offset_y, SOUTH, 125, WEST, 150);
	init_corner(&ui->bottom_right_corner, center_x + offset_x, center_y + offset_y, NORTH, 125, WEST, 350);
	init_corner(&ui->bottom_left_corner, center_x - offset_x, center_y + offset_y, NORTH, 125, EAST, 300);

	int local_offset = 30;

	ui->top_left_corner.org_x -= local_offset;
	ui->top_left_corner.org_y -= local_offset;
	ui->bottom_right_corner.org_x += local_offset;
	ui->bottom_right_corner.org_y += local_offset;
}
