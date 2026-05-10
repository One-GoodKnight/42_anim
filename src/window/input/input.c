#include "window/input.h"
#include "raylib.h"
#include "utils/utf8.h"
#include <string.h>

void	init_input(t_input *input)
{
	input->text[0] = '\0';
	input->utf8[0] = '\0';
	input->len = 0;
	input->cursor_i = 0;
	input->blink = 0;
	input->active = false;
}

void	handle_input(t_input *input)
{
	if (input->active == false)
		return ;

	int key = GetCharPressed();
	while (key > 0)
	{
		if (key == 160)  // breaking space
			key = ' ';
		if (key == 173) // soft hyphen (invisible)
			continue ;

		if (input->len < INPUT_MAX_LEN && key >= ' ' && key <= 255)
		{
			memmove(input->text + (input->cursor_i + 1), input->text + (input->cursor_i), input->len - (input->cursor_i));
			input->text[input->cursor_i] = (unsigned char)key;
			input->len++;
			input->text[input->len] = '\0';
			input->cursor_i++;
		}

		key = GetCharPressed();
	}

	input_suppression(input);
	input_movement(input);

	latin1_to_utf8(input->utf8, input->text);
}

