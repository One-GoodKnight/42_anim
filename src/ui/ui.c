#include "ui/corner.h"
#include "ui/msg_popup.h"
#include "ui/ui.h"
#include "raylib.h"
#include "ui/train.h"
#include "vector2.h"
#include <stddef.h>

static void	init_corners(t_ui *ui)
{
	int	center_x = ui->width / 2;
	int	center_y = ui->height / 2;

	int offset_x = BOX_WIDTH / 2;
	int offset_y = BOX_HEIGHT / 2;

	init_corner(ui, &ui->top_left_corner, center_x - offset_x, center_y - offset_y, SOUTH, 125, EAST, 250);
	init_corner(ui, &ui->top_right_corner, center_x + offset_x, center_y - offset_y, SOUTH, 125, WEST, 150);
	init_corner(ui, &ui->bottom_right_corner, center_x + offset_x, center_y + offset_y, NORTH, 125, WEST, 350);
	init_corner(ui, &ui->bottom_left_corner, center_x - offset_x, center_y + offset_y, NORTH, 125, EAST, 300);

	int local_offset = 30;

	ui->top_left_corner.org.x -= local_offset;
	ui->top_left_corner.org.y -= local_offset;
	ui->bottom_right_corner.org.x += local_offset;
	ui->bottom_right_corner.org.y += local_offset;
}

void	init_train(t_ui *ui)
{
	t_train *pika_choo = &ui->pika_choo;
	int		train_width = ui->train.width;

	ui->show_qst = false;

	pika_choo->width = train_width;
	
	// make the train appear at the same x cord for all resolutions
	// so that the questions shows at the same time
	int	max_supported_width = 3840;
	int	universal_relative_x = ui->width - max_supported_width;

	pika_choo->pos.x = universal_relative_x - train_width;
	pika_choo->pos.y = ui->height / 2.0f - 131;

	pika_choo->vel.x = TRAIN_INIT_VEL;
	pika_choo->vel.y = 0;
}

void	init_ui(t_ui *ui)
{
	int monitor = GetCurrentMonitor();
    int width   = GetMonitorWidth(monitor);
    int height  = GetMonitorHeight(monitor);

	ui->width = width;
	ui->height = height;

	ui->dt = 0;
	ui->state = BACKGROUND_FADE;

	ui->fade_progress = 0;
	ui->time_question_popped = 0;
	ui->result_screen_time_left = RESULT_SCREEN_TIME;

	vec_init(&ui->messages_popups, sizeof(t_msg_popup), NULL);

	init_corners(ui);
	
	// assets
	ui->fonts.font.glyphs = NULL;
	ui->fonts.font_popups.glyphs = NULL;
	ui->fonts.font_anim.glyphs = NULL;
}

int	release_ui(t_ui *ui)
{
	if (ui->fonts.font.glyphs)
		UnloadFont(ui->fonts.font);

	if (ui->fonts.font_popups.glyphs)
		UnloadFont(ui->fonts.font_popups);

	if (ui->fonts.font_anim.glyphs)
		UnloadFont(ui->fonts.font_anim);

	if (ui->logo.id != 0)
		UnloadTexture(ui->logo);

	if (ui->crown.id != 0)
		UnloadTexture(ui->crown);

	if (ui->train.id != 0)
		UnloadTexture(ui->train);

	vec_free(&ui->messages_popups);

	return (-1);
}
