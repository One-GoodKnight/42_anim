#ifndef TRAIN_H
# define TRAIN_H

# include "vector2.h"

# define TRAIN_INIT_VEL 1000
# define TRAIN_SPEED 1400

# define TRAIN_COOLDOWN 1.0f

typedef struct s_train
{
	t_vector2	pos;
	t_vector2	vel;
	int			width;
	float		cooldown;
}	t_train;

#endif
