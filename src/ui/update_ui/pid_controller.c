#include "ui/update_ui/pid_controller.h"
#include "ui/ui.h"

static t_vector2	compute_error(t_corner corner)
{
	t_vector2	error;

	error.x = corner.tar.x - corner.org.x;
	error.y = corner.tar.y - corner.org.y;

	return (error);
}

static void	move_system(float dt, t_corner *corner, t_pid_controller pid)
{
	t_vector2	error;

	error = compute_error(*corner);

	corner->vel.x += error.x * pid.p * dt;
	corner->vel.y += error.y * pid.p * dt;

	corner->vel.x += (error.x - corner->prev_err.x) / dt * pid.d;
	corner->vel.y += (error.y - corner->prev_err.y) / dt * pid.d;
	
	corner->org.x += corner->vel.x * dt;
	corner->org.y += corner->vel.y * dt;

	corner->prev_err = error;
}

void	apply_pid_controller(t_ui *ui, t_pid_controller pid)
{
	float dt;

	dt = ui->dt;
	move_system(dt, &ui->top_left_corner, pid);
	move_system(dt, &ui->top_right_corner, pid);
	move_system(dt, &ui->bottom_right_corner, pid);
	move_system(dt, &ui->bottom_left_corner, pid);

	if (
		ui->top_left_corner.prev_err.x / ui->dt < 50 &&
		ui->top_left_corner.prev_err.y / ui->dt < 50 &&
		ui->top_right_corner.prev_err.x / ui->dt < 50 &&
		ui->top_right_corner.prev_err.y / ui->dt < 50 &&
		ui->bottom_right_corner.prev_err.x / ui->dt < 50 &&
		ui->bottom_right_corner.prev_err.y / ui->dt < 50 &&
		ui->bottom_left_corner.prev_err.x / ui->dt < 50 &&
		ui->bottom_left_corner.prev_err.y / ui->dt < 50
	)
		ui->state = SHOW_TEXT;
}

void	init_pid_controller(t_pid_controller *pid)
{
	pid->p = PID_P;
	pid->d = PID_D;
}
