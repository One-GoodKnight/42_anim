#ifndef PID_CONTROLLER_H
# define PID_CONTROLLER_H

# define PID_P 8.0f
# define PID_D 0.1f

typedef struct s_pid_controller
{
	float	p;
	float	d;
}	t_pid_controller;

void	init_pid_controller(t_pid_controller *pid);

#endif
