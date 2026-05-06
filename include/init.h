#ifndef INIT_H
# define INIT_H

# include "file_op/data.h"
# include "raylib.h"

void	set_random_seed(void);
int		load_data(t_data *data);
Font	init_font(void);

#endif
