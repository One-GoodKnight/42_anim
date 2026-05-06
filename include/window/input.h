#ifndef INPUT_H
# define INPUT_H

# include <stddef.h>

# define INPUT_MAX_LEN 30

typedef struct s_input
{
	unsigned char	text[INPUT_MAX_LEN + 1];
	unsigned char	utf8[INPUT_MAX_LEN * 2 + 1];
	size_t			len;
	size_t			cursor_i;
}	t_input;

void	init_input(t_input *input);
void	handle_input(t_input *input);

#endif
