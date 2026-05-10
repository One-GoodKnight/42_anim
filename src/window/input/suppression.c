#include "window/input.h"
#include "raylib.h"
#include "string.h"

static bool	backspace(t_input *input)
{
	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
    	if (input->len > 0 && input->cursor_i != 0)
		{
			memmove(input->text + (input->cursor_i - 1), input->text + input->cursor_i, input->len - input->cursor_i);
			input->len--;
			input->text[input->len] = '\0';
			input->cursor_i--;
		}
		return (true);
	}

	return (false);
}

static bool ctrl_backspace(t_input *input)
{
	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_BACKSPACE) || (IsKeyPressedRepeat(KEY_BACKSPACE))))
	{
		int	prev_cursor_i = input->cursor_i;
		ctrl_arrow_left(input, true);

		int	diff = input->cursor_i - prev_cursor_i;
		diff = diff >= 0 ? diff : diff * -1;
		input->cursor_i = prev_cursor_i;

		for (int i = 0; i < diff; i++)
			backspace(input);
		return (true);
	}

	return (false);
}

static bool suppr(t_input *input)
{
	if (IsKeyPressed(KEY_DELETE) || IsKeyPressedRepeat(KEY_DELETE))
	{
    	if (input->len > 0 && input->cursor_i != input->len)
		{
			memmove(input->text + input->cursor_i, input->text + (input->cursor_i + 1), input->len - input->cursor_i);
			input->len--;
			input->text[input->len] = '\0';
		}
		return (true);
	}

	return (false);
}

static bool	ctrl_suppr(t_input *input)
{
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_DELETE))
	{
		int	prev_cursor_i = input->cursor_i;
		ctrl_arrow_right(input, true);

		int	diff = input->cursor_i - prev_cursor_i;
		diff = diff >= 0 ? diff : diff * -1;
		input->cursor_i = prev_cursor_i;

		for (int i = 0; i < diff; i++)
			suppr(input);
		return (true);
	}

	return (false);
}

void	input_suppression(t_input *input)
{
	bool	deleted;

	deleted = ctrl_backspace(input);

	if (!deleted)
		deleted = ctrl_suppr(input);

	if (!deleted)
		deleted = backspace(input);

	if (!deleted)
		deleted = suppr(input);
}
