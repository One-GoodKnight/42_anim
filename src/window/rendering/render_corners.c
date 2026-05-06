#include "raylib.h"
#include "window/rendering/colors.h"
#include "window/rendering/ui.h"

static void	render_line(int x, int y, int thickness, t_dir dir, int length)
{
	switch (dir)
	{
		case EAST:
			DrawRectangle(x, y, length, thickness, BORDER_COLOR);
			break;
		case SOUTH:
			DrawRectangle(x, y, thickness, length, BORDER_COLOR);
			break;
		case WEST:
			DrawRectangle(x - length + thickness, y, length, thickness, BORDER_COLOR);
			break;
		case NORTH:
			DrawRectangle(x, y - length + thickness, thickness, length, BORDER_COLOR);
			break;
	}
}

static void	render_corner(t_corner corner)
{
	render_line(corner.org_x + corner.x_offset, corner.org_y + corner.y_offset, corner.thickness, corner.line_one_dir, corner.line_one_length);
	render_line(corner.org_x + corner.x_offset, corner.org_y + corner.y_offset, corner.thickness, corner.line_two_dir, corner.line_two_length);
}

void	render_corners(t_ui *ui)
{
	render_corner(ui->top_left_corner);
	render_corner(ui->top_right_corner);
	render_corner(ui->bottom_right_corner);
	render_corner(ui->bottom_left_corner);
}
