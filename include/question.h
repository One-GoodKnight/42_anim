#ifndef QUESTION_H
# define QUESTION_H

# define MAX_ADDITION_SOUSTRACTION 100
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
	SOUSTRACTION,
	MULTIPLICATION,
	DIVISION
}	t_op;

typedef struct s_str_qst
{
	char	*str_sol;
	char	*mixed;
}	t_str_qst;

typedef struct s_nb_qst
{
	int		n1;
	int		n2;
	t_op	op;
	int		nb_sol;
}	t_nb_qst;

typedef struct s_qst
{
	t_mode		mode;
	t_str_qst	*str_qst;
	t_nb_qst	*str_qst;
}	t_qst;

#endif
