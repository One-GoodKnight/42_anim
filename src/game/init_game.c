#include "game/game.h"

void	init_game(t_game *game)
{
	game->question[0] = '\0';

	game->state = WAITING;
}
