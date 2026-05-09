#ifndef TRAIN_H
# define TRAIN_H

# include "vector2.h"

# define TRAIN_INIT_VEL 1000
# define TRAIN_SPEED 1400

typedef struct s_train
{
	t_vector2	pos;
	t_vector2	vel;
	int			width;
}	t_train;

#endif
