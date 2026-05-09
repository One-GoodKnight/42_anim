#include "game/question.h"
#include <stdlib.h>
#include <string.h>

void	init_question(t_qst *qst, t_data *data)
{
	if (DEBUG_EASY_QST == 1)
	{
		qst->mode = STR;
		qst->data.qst.text = malloc(2);
		qst->data.qst.utf8 = malloc(2);
		strcpy((char *)qst->data.qst.text, "1");
		strcpy((char *)qst->data.qst.utf8, "1");
		qst->data.str_qst.ans = qst->data.qst.text;
		return ;
	}

	qst->data.qst.text = NULL;
	qst->data.qst.utf8 = NULL;
	qst->mode = rand() % (MODE_COUNT);
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
	if (!qst)
		return ;

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
