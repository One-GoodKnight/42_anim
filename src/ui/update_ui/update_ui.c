#include "ui/update_ui/pid_controller.h"
#include "ui/update_ui/update_ui.h"
#include "ui/ui.h"
#include "raylib.h"

static void fade(t_ui *ui)
{
	ui->fade_progress += ui->dt * FADE_SPEED;

	if (ui->fade_progress >= 1)
	{
		ui->fade_progress = 1;
		ui->state = TRAIN_TRANSITION;
	}
}

void	update_ui(t_ui *ui, t_pid_controller *pid, char *qst)
{
	ui->dt = GetFrameTime();
	if (ui->dt == 0)
		ui->dt = 1.0f / 60.0f;  // simulate a frame to not break first tick of animations

	if (ui->state == BACKGROUND_FADE)
		fade(ui);

	update_train(ui, qst);
	apply_pid_controller(ui, *pid);
	floating_corners(ui);
	update_msg_popups(ui);
}
