#ifndef INPUT_H
# define INPUT_H

# include <stdbool.h>
# include <stddef.h>

# define INPUT_MAX_LEN 30

# define BLINK 0.5f

typedef struct s_input
{
	unsigned char	text[INPUT_MAX_LEN + 1];
	unsigned char	utf8[INPUT_MAX_LEN * 2 + 1];
	size_t			len;
	size_t			cursor_i;
	double			blink;
	bool			active;
}	t_input;

void	init_input(t_input *input);
bool	is_sep(unsigned char c);
void	handle_input(t_input *input);
void	input_suppression(t_input *input);
void	input_movement(t_input *input);
bool 	ctrl_arrow_left(t_input *input, bool force);
bool	ctrl_arrow_right(t_input *input, bool force);

#endif
