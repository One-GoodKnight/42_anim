#include "input.h"
#include "raylib.h"
#include "ui.h"
#include <string.h>

void	init_input(t_input *input)
{
	input->text[0] = '\0';
	input->max_len = INPUT_MAX_LEN;
	input->len = 0;
	input->cursor_i = 1;
}

void	handle_input(t_input *input)
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if (input->len < INPUT_MAX_LEN - 1 && key >= ' ' && key <= '~')
		{
			memcpy(input->text + (input->cursor_i), input->text + (input->cursor_i - 1), input->len - (input->cursor_i - 1));
			input->text[input->cursor_i - 1] = (char)key;
			input->len++;
			input->text[input->len] = '\0';
			input->cursor_i++;
		}
		key = GetCharPressed();
	}

	//backspace
	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
    	if (input->len > 0 && input->cursor_i != 1)
		{
			memcpy(input->text + (input->cursor_i - 2), input->text + (input->cursor_i - 1), input->len - (input->cursor_i) + 1);
			input->len--;
			input->text[input->len] = '\0';
			input->cursor_i--;
		}
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_BACKSPACE))
	{
		memcpy(input->text, input->text + (input->cursor_i - 1), input->len - (input->cursor_i) + 1);
		input->len = input->len - (input->cursor_i) + 1;
		input->text[input->len] = '\0';
		input->cursor_i = 1;
	}

	//del
	if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE))
	{
    	if (input->len > 0 && input->cursor_i - 1 != input->len)
		{
			memcpy(input->text + (input->cursor_i - 1), input->text + (input->cursor_i), input->len - (input->cursor_i));
			input->len--;
			input->text[input->len] = '\0';
		}
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_DELETE))
	{
		input->len = input->cursor_i - 1;
		input->text[input->len] = '\0';
	}

	//arrows
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
	{
		if (input->cursor_i > 1)
			input->cursor_i--;
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
	{
		if (input->cursor_i <= input->len)
			input->cursor_i++;
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT))
	{
		input->cursor_i = 1;
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_RIGHT))
	{
		input->cursor_i = input->len + 1;
	}
}

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
	int	text_width = MeasureTextEx(font, input->text, (float)font.baseSize, FONT_SPACING).x;
	input->text[input->cursor_i - 1] = erased;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	cursor_x = x + text_width + (input->cursor_i == 1 ? 0 : spacing_width(font));
	int	cursor_y = y;
	DrawRectangle(cursor_x, cursor_y, 2, text_height, FONT_COLOR);
}

#include <stdio.h>
void	render_input(t_input *input, int x, int y, Font font)
{
	DrawTextEx(font, input->text, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
	
	//cursor
	render_cursor(input, x, y, font);
}
