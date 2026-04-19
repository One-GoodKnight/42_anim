#include "logic/question.h"
#include "utils/utils.h"
#include "utils/utf8.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
void	shuffle_text(unsigned char *text)
{
	size_t	len;
	size_t	i;
	size_t	rand_i;

	len = ft_strlen(text);
	i = 0;
	while (text[i])
	{
		rand_i = rand() % len;
		swap_uchar(&text[i], &text[rand_i]);
		i++;
	}
}

t_shuf_str_qst	generate_shuf_str_question(t_data *data)
{
	t_shuf_str_qst	qst;

	qst.text = NULL;
	qst.utf8 = NULL;
	if (data->count == 0)
		return (qst);

	// get random line from data
	int	randint = rand() % (data->count);
	qst.text = malloc(sizeof(unsigned char) * (ft_strlen(data->lines[randint]) + 1));
	if (!qst.text)
		return (qst);

	// set answer before shuffle
	utf8_to_latin1(qst.text, data->lines[randint]);
	qst.ans = (unsigned char *)strdup((const char *)qst.text);
	if (!qst.ans)
		return qst;

	shuffle_text(qst.text);

	qst.utf8 = malloc(sizeof(unsigned char) * (ft_strlen(data->lines[randint]) + 1));
	if (!qst.utf8)
	{
		free(qst.ans);
		return (qst);
	}
	latin1_to_utf8(qst.utf8, qst.text);
	return (qst);
}
