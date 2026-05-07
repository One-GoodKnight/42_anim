#include "ui/update_ui/pid_controller.h"
#include "ui/ui.h"
#include <stdio.h>

static t_vector2	compute_error(t_corner corner)
{
	t_vector2	error;

	error.x = corner.tar_x - corner.org_x;
	error.y = corner.tar_y - corner.org_y;

	return (error);
}

static void	move_system(t_corner *corner)
{
	t_vector2	error;

	error = compute_error(*corner);
}

void	apply_pid_controller(t_ui *ui)
{
	printf("%f\n", ui->dt);
}

void	init_pid_controller(t_pid_controller *pid_controller)
{
	pid_controller->p = 1.0f;
	pid_controller->d = 1.0f;
}
