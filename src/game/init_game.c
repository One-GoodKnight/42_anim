#include "game/game.h"

void	init_game(t_game *game)
{
	game->question[0] = '\0';

	game->state = WAITING;

	game->winner_name[0] = '\0';
	game->winner_time = 0;
}
