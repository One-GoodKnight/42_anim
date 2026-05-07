#ifndef CORNER_H
# define CORNER_H

# include "vector2.h"

# define FLOATING_FREQUENCY_1 1
# define FLOATING_FREQUENCY_2 2
# define FLOATING_FREQUENCY_3 3

# define FLOATING_AMPLITUDE_1 4
# define FLOATING_AMPLITUDE_2 2
# define FLOATING_AMPLITUDE_3 1

typedef struct	s_ui t_ui;

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
} t_dir;

typedef struct s_corner
{
	t_vector2	tar;

	int			thickness;

	t_dir		line_one_dir;
	int			line_one_length;

	t_dir		line_two_dir;
	int			line_two_length;

	// pid controller animation, bring the borders to the screen
	t_vector2	org;
	t_vector2	vel;
	t_vector2	prev_err;

	// floating animation
	t_vector2	offset;

	float		phase;  // random start in the trig circle
}	t_corner;

void	init_corner(t_ui *ui, t_corner *corner, int x, int y, t_dir line_one_dir, int line_one_length, t_dir line_two_dir, int line_two_length);

#endif
