#include "window/input.h"
#include "window/rendering/ui.h"

int	spacing_width(Font font)
{
	int	single_char = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).x;
	int	double_char = MeasureTextEx(font, "||", (float)font.baseSize, FONT_SPACING).x;
	return (double_char - 2*single_char);
}

void	render_cursor(t_input *input, int x, int y, Font font)
{
	char	erased = input->text[input->cursor_i - 1];
	input->text[input->cursor_i - 1] = '\0';
	int	text_width = MeasureTextEx(font, (char *)input->text, (float)font.baseSize, FONT_SPACING).x;
	input->text[input->cursor_i - 1] = erased;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	cursor_x = x + text_width + (input->cursor_i == 1 ? 0 : spacing_width(font));
	int	cursor_y = y;
	DrawRectangle(cursor_x, cursor_y, 2, text_height, FONT_COLOR);
}

void	render_input(t_input *input, int x, int y, Font font)
{
	DrawTextEx(font, (char *)input->utf8, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
	render_cursor(input, x, y, font);
}
