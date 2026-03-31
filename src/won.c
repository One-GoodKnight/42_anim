#include "input.h"
#include "question.h"
#include "utils.h"
#include "raylib.h"
#include <stdbool.h>

#include <stdio.h>
bool	won(t_input *input, t_qst *qst)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		if (qst->mode == STRING && ft_strcmp(input->text, qst->data.str_qst.ans) == 0)
			return (true);
		if (qst->mode == NUMBER && ft_uatoi(input->text) == (unsigned int)qst->data.nb_qst.ans)
			return (true);
	}
	return (false);
}
