#include "window/input.h"
#include "raylib.h"

bool ctrl_arrow_left(t_input *input, bool force)
{
	if (force || (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))))
	{
		int i = input->cursor_i - 1;
		if (i == -1)
			return (true);

		while (i >= 0 && is_sep(input->text[i]))
			i--;
		while (i >= 0 && !is_sep(input->text[i]))
			i--;

		input->cursor_i = i + 1;

		return (true);
	}

	return (false);
}

bool	ctrl_arrow_right(t_input *input, bool force)
{
	if (force || (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))))
	{
		int	input_len = (int)input->len;

		int i = input->cursor_i;
		if (i == input_len)
			return (true);

		while (i < input_len && is_sep(input->text[i]))
			i++;
		while (i < input_len && !is_sep(input->text[i]))
			i++;

		input->cursor_i = i;

		return (true);
	}

	return (false);
}

static bool	arrow(t_input *input)
{
	bool moved = false;

	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
	{
		if (input->cursor_i > 0)
			input->cursor_i--;
		moved = true;
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
	{
		if (input->cursor_i < input->len)
			input->cursor_i++;
		moved = true;
	}

	return (moved);
}

void	input_movement(t_input *input)
{
	bool	moved;

	moved = ctrl_arrow_left(input, false);

	if (!moved)
		moved = ctrl_arrow_right(input, false);

	if (!moved)
		moved = arrow(input);
}
