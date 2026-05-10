#include "window/input.h"
#include "utils/utils.h"
#include "raylib.h"
#include "string.h"

void	input_movement(t_input *input)
{
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
}
