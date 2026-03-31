#ifndef QUESTION_H
# define QUESTION_H

# include "data.h"

# define RATIO_STRING_NB 2

# define MAX_ADDITION_SUBSTRACTION 100
# define MAX_MULTIPLICATION 20

# define MAX_DIVISION 100

typedef enum e_mode
{
	STRING,
	NUMBER
}	t_mode;

typedef enum e_op
{
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVISION,
	OP_COUNT
}	t_op;

typedef struct s_str_qst
{
	unsigned char	*text;
	unsigned char			*utf8;
	unsigned char	*ans;
}	t_str_qst;

typedef struct s_nb_qst
{
	unsigned char	*text;
	unsigned char	*utf8;
	int				ans;
	int				n1;
	int				n2;
	t_op			op;
}	t_nb_qst;

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
		t_str_qst	str_qst;
		t_nb_qst	nb_qst;
	}	data;
}	t_qst;

void	init_question(t_qst *qst, t_data *data);

#endif
