#ifndef CORNER_H
# define CORNER_H

# define FLOATING_FREQUENCY_1 1
# define FLOATING_FREQUENCY_2 2
# define FLOATING_FREQUENCY_3 3
# define FLOATING_AMPLITUDE_1 6
# define FLOATING_AMPLITUDE_2 4
# define FLOATING_AMPLITUDE_3 2

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

	int		thickness;

	t_dir	line_one_dir;
	int		line_one_length;

	t_dir	line_two_dir;
	int		line_two_length;

	// floating animation
	float	x_offset;
	float	y_offset;

	float	phase;	// random start in the trig circle
}	t_corner;

#endif
