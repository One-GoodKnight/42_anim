#ifndef CORNER_H
# define CORNER_H

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
} t_dir;

typedef struct s_corner
{
	int		org_x;
	int		org_y;

	int		x_offset;
	int		y_offset;

	int		thickness;

	t_dir	line_one_dir;
	int		line_one_length;

	t_dir	line_two_dir;
	int		line_two_length;
}	t_corner;

#endif
