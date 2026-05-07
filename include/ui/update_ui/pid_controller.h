#ifndef PID_CONTROLLER_H
# define PID_CONTROLLER_H

typedef struct	s_vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct s_pid_controller
{
	float	p;
	float	d;
}	t_pid_controller;

void	init_pid_controller(t_pid_controller *pid_controller);

#endif
