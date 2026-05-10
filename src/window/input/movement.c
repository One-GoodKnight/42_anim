#include "window/input.h"
#include "raylib.h"

static void	arrow(t_input *input)
{
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
	{
		if (input->cursor_i > 0)
			input->cursor_i--;
	}

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
	{
		if (input->cursor_i < input->len)
			input->cursor_i++;
	}
}

static void ctrl_arrow_left(t_input *input)
{
	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)))
	{
		int i = input->cursor_i - 1;
		if (i == -1)
			return ;

		while (i >= 0 && is_sep(input->text[i]))
			i--;
		while (i >= 0 && is_sep(input->text[i]))
			i--;

		input->cursor_i = i + 1;
	}
}

static void	ctrl_arrow_right(t_input *input)
{
	if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)))
	{
		int	input_len = (int)input->len;

		int i = input->cursor_i;
		if (i == input_len)
			return ;

		while (i < input_len && is_sep(input->text[i]))
			i++;
		while (i < input_len && is_sep(input->text[i]))
			i++;

		input->cursor_i = i;
	}
}

void	input_movement(t_input *input)
{
	arrow(input);
	ctrl_arrow_left(input);
	ctrl_arrow_right(input);
}
