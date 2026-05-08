#include "ui/update_ui/pid_controller.h"
#include "ui/update_ui/update_ui.h"
#include "ui/ui.h"
#include "raylib.h"
#include <stdio.h>

static void fade(t_ui *ui)
{
	ui->fade_progress += ui->dt * FADE_SPEED;

	if (ui->fade_progress >= 1)
	{
		ui->fade_progress = 1;
		ui->state = BRING_BORDERS;
	}
}

void	update_ui(t_ui *ui, t_pid_controller *pid)
{
	ui->dt = GetFrameTime();

	if (ui->state == BACKGROUND_FADE)
		fade(ui);

	if (ui->state == BRING_BORDERS)
		apply_pid_controller(ui, *pid);

	//if (ui->state == SHOW_TEXT)
	//	printf("SHOW_TEXT\n");

	floating_corners(ui);
	update_msg_popups_ttl(ui);
}
