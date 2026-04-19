#include "window/input.h"
#include "logic/question.h"
#include "utils/utils.h"
#include "raylib.h"

bool	won(t_input *input, t_qst *qst)
{
	unsigned int	out_uatoi;

	if (IsKeyPressed(KEY_ENTER))
	{
		switch (qst->mode)
		{
			case NB:
				if (ft_uatoi(input->text, &out_uatoi) && out_uatoi == (unsigned int)qst->data.nb_qst.ans)
					return (true);
				break;
			case STR:
				if (ft_strcmp(input->text, qst->data.str_qst.ans) == 0)
					return (true);
				break;
			case SHUF_STR:
				if (ft_strcmp(input->text, qst->data.shuf_str_qst.ans) == 0)
					return (true);
				break;
			case MODE_COUNT:
				break;
		}
	}
	return (false);
}
