#include "ui/ui.h"
#include "vector2.h"
#include "stdlib.h"
#include "raylib.h"

static t_vector2	compute_semi_rand_pos(t_ui *ui, t_corner *corner, t_dir line_one_dir, t_dir line_two_dir)
{
	t_vector2	pos = {0};

	if (corner == &ui->top_left_corner)
	{
		t_dir	dir = WEST;

		if (rand() % 2 == 0)
			dir = NORTH;

		if (dir == WEST)
			pos = (t_vector2){0, rand() % (ui->height / 2 + 1)};

		if (dir == NORTH)
			pos = (t_vector2){rand() % (ui->width / 2 + 1), 0};

		pos.x -= corner->line_two_length;
		pos.y -= corner->line_one_length;
		return (pos);
	}

	if (corner == &ui->top_right_corner)
	{
		t_dir	dir = EAST;

		if (rand() % 2 == 0)
			dir = NORTH;

		if (dir == EAST)
			pos = (t_vector2){ui->width, rand() % (ui->height / 2 + 1)};

		if (dir == NORTH)
			pos = (t_vector2){ui->width / 2.0f + rand() % (ui->width / 2 + 1), 0};

		pos.y -= corner->line_one_length;
		return (pos);
	}

	if (corner == &ui->bottom_right_corner)
	{
		t_dir	dir = SOUTH;

		if (rand() % 2 == 0)
			dir = EAST;

		if (dir == SOUTH)
			pos = (t_vector2){ui->width / 2.0f + rand() % (ui->width / 2 + 1), ui->height};

		if (dir == EAST)
			pos = (t_vector2){ui->width, ui->height / 2.0f + rand() % (ui->height / 2 + 1)};

		return (pos);
	}

	if (corner == &ui->bottom_left_corner)
	{
		t_dir	dir = SOUTH;

		if (rand() % 2 == 0)
			dir = WEST;

		if (dir == SOUTH)
			pos = (t_vector2){rand() % (ui->width / 2 + 1), ui->height};

		if (dir == WEST)
			pos = (t_vector2){0, rand() % (ui->height / 2 + 1)};

		pos.x -= corner->line_two_length;
		return (pos);
	}

	return (pos);
}

void	init_corner(
		t_ui	*ui,
		t_corner *corner,
		int x,
		int y,
		t_dir line_one_dir,
		int line_one_length,
		t_dir line_two_dir,
		int line_two_length
){
	corner->tar = (t_vector2){x, y};

	corner->thickness = BORDER_THICKNESS;

	corner->line_one_dir = line_one_dir;
	corner->line_one_length = line_one_length;

	corner->line_two_dir = line_two_dir;
	corner->line_two_length = line_two_length;

	// pid controller animation, bring the borders to the screen
	corner->org = compute_semi_rand_pos(ui, corner, line_one_dir, line_two_dir);
	corner->vel = (t_vector2){0, 0};
	corner->prev_err = (t_vector2){0, 0};

	// floating animation
	corner->offset = (t_vector2){0, 0};

	float	t = (float)rand() / (float)RAND_MAX;
	corner->phase = PI * 2 * t;
}
