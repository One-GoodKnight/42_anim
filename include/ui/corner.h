#ifndef CORNER_H
# define CORNER_H

# define FLOATING_FREQUENCY_1 1
# define FLOATING_FREQUENCY_2 2
# define FLOATING_FREQUENCY_3 3

# define FLOATING_AMPLITUDE_1 4
# define FLOATING_AMPLITUDE_2 2
# define FLOATING_AMPLITUDE_3 1

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
} t_dir;

typedef struct s_corner
{
	int		tar_x;
	int		tar_y;

	int		thickness;

	t_dir	line_one_dir;
	int		line_one_length;

	t_dir	line_two_dir;
	int		line_two_length;

	// pid controller animation, bring the borders to the screen
	float	org_x;
	float	org_y;

	// floating animation
	float	x_offset;
	float	y_offset;

	float	phase;  // random start in the trig circle
}	t_corner;

#endif
