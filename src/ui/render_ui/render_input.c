#include "ui/render_ui/colors.h"
#include "ui/ui.h"
#include "window/input.h"
#include "raylib.h"

static int	spacing_width(Font font)
{
	int	single_char = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).x;
	int	double_char = MeasureTextEx(font, "||", (float)font.baseSize, FONT_SPACING).x;
	return (double_char - 2*single_char);
}

static void	render_cursor(t_input *input, int x, int y, Font font)
{
	// make the text of the input end at cursor temporary to get width from start to cursor
	char	erased = input->text[input->cursor_i];
	input->text[input->cursor_i] = '\0';
	int	text_width = MeasureTextEx(font, (char *)input->text, (float)font.baseSize, FONT_SPACING).x;
	input->text[input->cursor_i] = erased;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	cursor_x = x + text_width + (input->cursor_i == 0 ? 0 : spacing_width(font));
	int	cursor_y = y;
	DrawRectangle(cursor_x, cursor_y, 2, text_height, FONT_COLOR);
}

static void	render_text(t_input *input, Font font, int x, int y)
{
	DrawTextEx(font, (char *)input->utf8, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
}

static void	update_cursor_blink(t_input *input, float dt)
{
	input->blink += dt;

	while (input->blink >= BLINK * 2)
		input->blink -= BLINK * 2;
}

void	render_input(t_ui *ui, char *qst, t_input *input, Font font)
{
	if (input->active == false)
		return ;

	int	qst_text_width = MeasureTextEx(font, qst, (float)font.baseSize, FONT_SPACING).x;

	int	x = ui->width / 2 - qst_text_width / 2;
	int	y = ui->height / 2;
	y += TEXT_Y_OFFSET;

	render_text(input, font, x, y);

	update_cursor_blink(input, ui->dt);
	if (input->blink > BLINK)
		return ;
	render_cursor(input, x, y, font);
}
