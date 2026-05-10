#include "window/input.h"
#include "raylib.h"
#include "string.h"

void	input_suppression(t_input *input)
{
	//backspace
	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
    	if (input->len > 0 && input->cursor_i != 0)
		{
			memmove(input->text + (input->cursor_i - 1), input->text + input->cursor_i, input->len - input->cursor_i);
			input->len--;
			input->text[input->len] = '\0';
			input->cursor_i--;
		}
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_BACKSPACE) || (IsKeyPressedRepeat(KEY_BACKSPACE))))
	{
		memmove(input->text, input->text + (input->cursor_i), input->len - input->cursor_i);
		input->len = input->len - input->cursor_i;
		input->text[input->len] = '\0';
		input->cursor_i = 0;
		update_utf8(input);
	}

	//del
	if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE))
	{
    	if (input->len > 0 && input->cursor_i != input->len)
		{
			memmove(input->text + input->cursor_i, input->text + (input->cursor_i + 1), input->len - input->cursor_i);
			input->len--;
			input->text[input->len] = '\0';
		}
		update_utf8(input);
	}

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_DELETE))
	{
		input->len = input->cursor_i;
		input->text[input->len] = '\0';
		update_utf8(input);
	}
}
