#include "question.h"
#include "utils.h"
#include "utf8.h"
#include <stdlib.h>

t_str_qst	generate_str_question(t_data *data)
{
	t_str_qst	qst;

	qst.text = NULL;
	qst.utf8 = NULL;
	if (data->count == 0)
		return (qst);
	int	randint = rand() % (data->count);
	qst.utf8 = data->lines[randint];
	qst.text = malloc(sizeof(unsigned char) * (ft_strlen(qst.utf8) + 1));
	if (!qst.text)
		return (qst);
	utf8_to_latin1(qst.text, qst.utf8);
	//temp
	qst.ans = qst.text;
	return (qst);
}

unsigned char	*build_question_text(int n1, int n2, char op)
{
	unsigned char	*text;

	text = malloc(uint_len(n1) + sizeof(' ') + sizeof(op) + sizeof(' ') + uint_len(n2) + 1);
	if (!text)
		return (NULL);
	uint_str(text, n1);
	append_char(text, ' ');
	append_char(text, op);
	append_char(text, ' ');
	uint_str(text + ft_strlen(text), n2);
	return (text);
}

int	find_divider(int n)
{
	size_t	count_dividers;
	int i;
	
	count_dividers = 0;
	i = 1;
	while (i <= n)
	{
		if (n % i == 0)
			count_dividers++;
		i++;
	}

	size_t	target_divider = (rand() % count_dividers) + 1;

	i = 1;
	while (i <= n)
	{
		if (n % i == 0)
			target_divider--;
		if (target_divider == 0)
			return (i);
		i++;
	}
	return (1);
}

t_nb_qst	generate_nb_question()
{
	t_nb_qst	qst;

	qst.op = rand() % OP_COUNT;
	switch (qst.op)
	{
		case ADDITION:
			qst.n1 = rand() % (MAX_ADDITION_SUBSTRACTION + 1);
			qst.n2 = rand() % (MAX_ADDITION_SUBSTRACTION + 1);
			qst.ans = qst.n1 + qst.n2;
			qst.text = build_question_text(qst.n1, qst.n2, '+');
			break;
		case SUBSTRACTION:
			qst.n1 = rand() % (MAX_ADDITION_SUBSTRACTION + 1);
			qst.n2 = rand() % (MAX_ADDITION_SUBSTRACTION + 1);
			if (qst.n1 < qst.n2)
			{
				qst.n1 += qst.n2;
				qst.n2 = qst.n1 - qst.n2;
				qst.n1 -= qst.n2;
			}
			qst.ans = qst.n1 - qst.n2;
			qst.text = build_question_text(qst.n1, qst.n2, '-');
			break;
		case MULTIPLICATION:
			qst.n1 = rand() % (MAX_MULTIPLICATION + 1);
			qst.n2 = rand() % (MAX_MULTIPLICATION + 1);
			qst.ans = qst.n1 * qst.n2;
			qst.text = build_question_text(qst.n1, qst.n2, 'x');
			break;
		case DIVISION:
			qst.n1 = rand() % (MAX_DIVISION + 1);
			qst.n2 = find_divider(qst.n1);
			qst.ans = qst.n1 / qst.n2;
			qst.text = build_question_text(qst.n1, qst.n2, '/');
			break;
		case OP_COUNT:
			break;
	}
	if (!qst.text)
		return (qst);
	qst.utf8 = malloc(ft_strlen(qst.text)*2 + 1);
	if (!qst.utf8)
		return (qst);
	latin1_to_utf8(qst.utf8, qst.text);
	return (qst);
}

void	init_question(t_qst *qst, t_data *data)
{
	int	randint = rand() % (RATIO_STRING_NB + 1);
	qst->mode = randint == 0 ? NUMBER : STRING;
	if (qst->mode == NUMBER)
		qst->data.nb_qst = generate_nb_question();
	else
		qst->data.str_qst = generate_str_question(data);
	if (!qst->data.qst.text || !qst->data.qst.utf8)
	{
		free(qst->data.qst.text);
		free(qst->data.qst.utf8);
		qst->data.qst.text = NULL;
		qst->data.qst.utf8 = NULL;
	}
}
