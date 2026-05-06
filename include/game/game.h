#ifndef GAME_H
# define GAME_H

typedef enum e_game_state
{
	WAITING,
	IN_GAME,
	RESULTS,
	FINNISHED,
}	t_game_state;

typedef struct s_game
{
	t_game_state	state;
	
	char			winner_name[256];
	float			winner_time;
}	t_game;

#endif
