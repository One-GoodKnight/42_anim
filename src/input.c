#include "input.h"
#include "raylib.h"
#include "ui.h"
#include "utf8.h"
#include "utils.h"
#include <string.h>

#include <stdio.h>

void	init_input(t_input *input)
{
	input->text[0] = '\0';
	input->utf8[0] = '\0';
	input->max_len = INPUT_MAX_LEN;
	input->len = 0;
	input->cursor_i = 1;
}

void	update_utf8(t_input *input)
{
	latin1_to_utf8(input->utf8, input->text);
}

void	handle_input(t_input *input)
{
	int key = GetCharPressed();
	while (key > 0)
	{
		if (input->len < INPUT_MAX_LEN && key >= ' ' && key <= 255)
		{
			memmove(input->text + (input->cursor_i), input->text + (input->cursor_i - 1), input->len - (input->cursor_i - 1));
			input->text[input->cursor_i - 1] = (unsigned char)key;
			input->len++;
			input->text[input->len] = '\0';
			input->cursor_i++;
		}
		key = GetCharPressed();
		update_utf8(input);
	}

	//backspace
	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
    	if (input->len > 0 && input->cursor_i != 1)
		{
			memmove(input->text + (input->cursor_i - 2), input->text + (input->cursor_i - 1), input->len - (input->cursor_i) + 1);
			input->len--;
			input->text[input->len] = '\0';
			input->cursor_i--;
		}
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_BACKSPACE) || (IsKeyPressedRepeat(KEY_BACKSPACE))))
	{
		memmove(input->text, input->text + (input->cursor_i - 1), (input->len) - (input->cursor_i - 1));
		input->len = input->len - (input->cursor_i) + 1;
		input->text[input->len] = '\0';
		input->cursor_i = 1;
		update_utf8(input);
	}

	//del
	if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE))
	{
    	if (input->len > 0 && input->cursor_i - 1 != input->len)
		{
			memmove(input->text + (input->cursor_i - 1), input->text + (input->cursor_i), input->len - (input->cursor_i - 1));
			input->len--;
			input->text[input->len] = '\0';
		}
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_DELETE))
	{
		input->len = input->cursor_i - 1;
		input->text[input->len] = '\0';
		update_utf8(input);
	}

	//arrows
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
	{
		if (input->cursor_i > 1)
			input->cursor_i--;
		update_utf8(input);
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
	{
		if (input->cursor_i <= input->len)
			input->cursor_i++;
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)))
	{
		int i = input->cursor_i - 2;
		while (i >= 0 && input->text[i + 1] == ' ')
			i--;
		while (i >= 0 && input->text[i] != ' ')
			i--;
		input->cursor_i = i + 2;
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)))
	{
		size_t i = input->cursor_i - 1;
		while (i < ft_strlen(input->text) && input->text[i - 1] == ' ')
			i++;
		while (i < ft_strlen(input->text) && input->text[i] != ' ')
			i++;
		input->cursor_i = i + 1;
		update_utf8(input);
	}
	//printf("%c\n", input->text[input->cursor_i]);
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
	int	text_width = MeasureTextEx(font, (char *)input->text, (float)font.baseSize, FONT_SPACING).x;
	input->text[input->cursor_i - 1] = erased;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	cursor_x = x + text_width + (input->cursor_i == 1 ? 0 : spacing_width(font));
	int	cursor_y = y;
	DrawRectangle(cursor_x, cursor_y, 2, text_height, FONT_COLOR);
}

#include <stdio.h>
void	render_input(t_input *input, int x, int y, Font font)
{
	DrawTextEx(font, (char *)input->utf8, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
	
	//cursor
	render_cursor(input, x, y, font);
}
