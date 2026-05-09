#ifndef GAME_H
# define GAME_H

# include "game/question.h"
# include <stdbool.h>

typedef enum e_game_state
{
	WAITING,
	IN_GAME,
	QST_RECEIVED,
	RESULTS,
	FINISHED,
}	t_game_state;

typedef struct s_game
{
	char			question[256];

	t_game_state	state;
}	t_game;

void	init_game(t_game *game);
bool	check_win(char *answer, t_qst *qst);

#endif
