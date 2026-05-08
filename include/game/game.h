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
	char			question[256];

	t_game_state	state;
}	t_game;

void	init_game(t_game *game);

#endif
