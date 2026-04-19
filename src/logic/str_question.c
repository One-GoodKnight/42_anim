#include "logic/question.h"
#include "utils/utils.h"
#include "utils/utf8.h"
#include <stdlib.h>
#include <string.h>

t_str_qst	generate_str_question(t_data *data)
{
	t_str_qst	qst;

	qst.text = NULL;
	qst.utf8 = NULL;
	if (data->count == 0)
		return (qst);
	int	randint = rand() % (data->count);
	qst.utf8 = (unsigned char *)(strdup((char *)(data->lines[randint])));
	if (!qst.utf8)
		return (qst);
	qst.text = malloc(sizeof(unsigned char) * (ft_strlen(qst.utf8) + 1));
	if (!qst.text)
		return (qst);
	utf8_to_latin1(qst.text, qst.utf8);
	qst.ans = qst.text;
	return (qst);
}
