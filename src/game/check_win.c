#include "game/question.h"
#include "utils/utils.h"

bool	check_win(char *answer, t_qst *qst)
{
	const unsigned char *ans = (const unsigned char *)answer;

	if (qst->mode == SHUF_STR)
	{
		if (ft_strcmp(ans, qst->data.shuf_str_qst.ans, trans_lower) == 0)
			return (true);
	}
	else
	{
		if (ft_strcmp(ans, qst->data.str_qst.ans, NULL) == 0)
			return (true);
	}

	return (false);
}
