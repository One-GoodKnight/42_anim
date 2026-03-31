#include "input.h"
#include "question.h"
#include "utils.h"
#include "raylib.h"
#include <stdbool.h>

bool	won(t_input *input, t_qst *qst)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		if (qst->mode == STRING && input->text == qst->data.str_qst.ans)
			return (true);
		if (qst->mode == NUMBER && ft_uatoi(input->text) == (unsigned int)qst->data.nb_qst.ans)
			return (true);
	}
	return (false);
}
