#include "game/game.h"
#include "ui/ui.h"
#include "net/message.h"
#include "net/network.h"
#include "string.h"

static void	process_winner(t_net *net, t_msg *msg, t_game *game)
{
	(void)net;
	if (strncmp(msg->msg, "WINNER:", strlen("WINNER:")) != 0)
		return ;

	strncpy((char *)&game->winner_name, msg->msg + strlen("WINNER:"), sizeof(game->winner_name) - 1);
	game->state = RESULTS;
}

void	process_msg_client_ui(t_net *net, t_ui *ui, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_winner(net, msg, game);
	}
}
