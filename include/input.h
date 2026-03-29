#ifndef INPUT_H
# define INPUT_H

# include <stddef.h>
# include "raylib.h"

# define INPUT_MAX_LEN 30

typedef struct s_input
{
	char	text[INPUT_MAX_LEN];
	size_t	max_len;
	size_t	len;
	size_t	cursor_i;
}	t_input;

void	init_input(t_input *input);
void	handle_input(t_input *input);
void	render_input(t_input *input, int x, int y, Font font);

#endif
