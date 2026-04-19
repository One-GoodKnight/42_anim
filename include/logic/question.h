#ifndef QUESTION_H
# define QUESTION_H

# include "file_op/data.h"

# define MAX_ADDITION_SUBSTRACTION 100
# define MAX_MULTIPLICATION 20

# define MAX_DIVISION 100

typedef enum e_mode
{
	NB,
	STR,
	SHUF_STR,
	MODE_COUNT
}	t_mode;

typedef enum e_op
{
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVISION,
	OP_COUNT
}	t_op;

typedef struct s_nb_qst
{
	unsigned char	*text;
	unsigned char	*utf8;
	int				ans;
	int				n1;
	int				n2;
	t_op			op;
}	t_nb_qst;

typedef struct s_str_qst
{
	unsigned char	*text;
	unsigned char	*utf8;
	unsigned char	*ans;
}	t_str_qst;

typedef struct s_shuf_str_qst
{
	unsigned char	*text;
	unsigned char	*utf8;
	unsigned char	*ans;
}	t_shuf_str_qst;

typedef struct s_qst
{
	t_mode		mode;
	union
	{
		struct
		{
			unsigned char	*text;
			unsigned char	*utf8;
		}	qst;
		t_nb_qst		nb_qst;
		t_str_qst		str_qst;
		t_shuf_str_qst	shuf_str_qst;
	}	data;
}	t_qst;

void			init_question(t_qst *qst, t_data *data);
t_nb_qst		generate_nb_question();
t_str_qst		generate_str_question(t_data *data);
t_shuf_str_qst	generate_shuf_str_question(t_data *data);
void			free_qst(t_qst *qst);

#endif
