#ifndef GAME_H
# define GAME_H

# include "game/question.h"

typedef enum e_game_state
{
	WAITING,
	IN_GAME,
	RESULTS,
}	t_game_state;

typedef struct s_game
{
	t_game_state	state;

	t_qst			*qst;
	
	char			*winner_name;
	float			winner_time;
}	t_game;

#endif
