#include "logic/question.h"
#include "utils/utils.h"
#include "utils/utf8.h"
#include <stdlib.h>
#include <string.h>

void	init_question(t_qst *qst, t_data *data)
{
	qst->data.qst.text = NULL;
	qst->data.qst.utf8 = NULL;
	qst->mode = rand() % (MODE_COUNT);
	qst->mode = SHUF_STR;
	switch(qst->mode)
	{
		case NB:
			qst->data.nb_qst = generate_nb_question();
			break;
		case STR:
			qst->data.str_qst = generate_str_question(data);
			break;
		case SHUF_STR:
			qst->data.shuf_str_qst = generate_shuf_str_question(data);
			break;
		case MODE_COUNT:
			break;
	}
	if (!qst->data.qst.text || !qst->data.qst.utf8)
	{
		free(qst->data.qst.text);
		free(qst->data.qst.utf8);
		qst->data.qst.text = NULL;
		qst->data.qst.utf8 = NULL;
	}
}

void	free_qst(t_qst *qst)
{
	free(qst->data.qst.utf8);
	qst->data.qst.utf8 = NULL;
	free(qst->data.qst.text);
	qst->data.qst.text = NULL;

	if (qst->mode == SHUF_STR)
	{
		free(qst->data.shuf_str_qst.ans);
		qst->data.shuf_str_qst.ans = NULL;
	}
}
