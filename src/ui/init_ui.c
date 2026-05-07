#include "ui/corner.h"
#include "ui/ui.h"
#include "raylib.h"
#include "vector2.h"

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

	init_corner(ui, &ui->top_left_corner, center_x - offset_x, center_y - offset_y, SOUTH, 125, EAST, 250);
	init_corner(ui, &ui->top_right_corner, center_x + offset_x, center_y - offset_y, SOUTH, 125, WEST, 150);
	init_corner(ui, &ui->bottom_right_corner, center_x + offset_x, center_y + offset_y, NORTH, 125, WEST, 350);
	init_corner(ui, &ui->bottom_left_corner, center_x - offset_x, center_y + offset_y, NORTH, 125, EAST, 300);

	int local_offset = 30;

	ui->top_left_corner.org.x -= local_offset;
	ui->top_left_corner.org.y -= local_offset;
	ui->bottom_right_corner.org.x += local_offset;
	ui->bottom_right_corner.org.y += local_offset;

	ui->result_screen_time_left = RESULT_SCREEN_TIME;
}
