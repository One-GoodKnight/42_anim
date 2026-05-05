#include "window/input.h"
#include "logic/question.h"
#include "utils/utils.h"
#include "raylib.h"
#include <stdio.h>

bool	check_win(char *answer, t_qst *qst)
{
	unsigned int	out_uatoi;

	const unsigned char *ans = (const unsigned char *)answer;
	switch (qst->mode)
	{
		case NB:
			if (ft_uatoi(ans, &out_uatoi) && out_uatoi == (unsigned int)qst->data.nb_qst.ans)
				return (true);
			break;
		case STR:
			if (ft_strcmp(ans, qst->data.str_qst.ans) == 0)
				return (true);
			break;
		case SHUF_STR:
			if (ft_strcmp_ignore_case(ans, qst->data.shuf_str_qst.ans) == 0)
				return (true);
			break;
		case MODE_COUNT:
			break;
	}
	return (false);
}
