#include "ui/train.h"
#include "ui/ui.h"
#include "utils/utils.h"

void	update_train(t_ui *ui, char *qst)
{
	t_train *pika_choo = &ui->pika_choo;

	if (pika_choo->pos.x < ui->width)
	{
		pika_choo->vel.x += TRAIN_SPEED * ui->dt;
		pika_choo->pos.x += pika_choo->vel.x * ui->dt;
	}

	if (ui->state == COMPLETE)
		return ;

	Font font = ui->fonts.font;
	int	qst_width = MeasureTextEx(font, qst, (float)font.baseSize, FONT_SPACING).x;

	// show text
	int qst_start_x = ui->width / 2 - qst_width / 2;

	if (ui->pika_choo.pos.x >= qst_start_x)
		ui->show_qst = true;

	// let user type and start timer
	int qst_end_x = ui->width / 2 + qst_width / 2;

	if (ui->pika_choo.pos.x >= qst_end_x)
	{
		ui->time_question_popped = get_time();
		ui->state = COMPLETE;
	}
}
