#include "game/game.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "net/message.h"
#include "net/network.h"
#include "utils/utils.h"
#include <string.h>

static void	process_winner(t_ui *ui, t_msg *msg, t_game *game)
{
	if (strncmp(msg->msg, "WINNER:", strlen("WINNER:")) != 0)
		return ;

	char *payload = msg->msg + strlen("WINNER:");

	char *separator = strchr(payload, '|');
	if (!separator)
		return ;

	char name[256];
	int name_len = separator - payload;
	strncpy(name, payload, name_len);
	name[name_len] = '\0';

	char *ans = separator + 1;

	float winner_time = get_time() - ui->time_question_popped;

	add_msg_popup(ui, name, ans, true, winner_time);
	game->state = RESULTS;
}

void	process_msg_client_ui(t_net *net, t_ui *ui, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_winner(ui, msg, game);
	}
}
