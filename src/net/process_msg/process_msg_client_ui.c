#include "game/game.h"
#include "net/message.h"
#include "net/network.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "utils/utf8.h"
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

	char name_utf8[512];
	latin1_to_utf8((unsigned char *)name_utf8, (unsigned char *)name);
	char ans_utf8[512];
	latin1_to_utf8((unsigned char *)ans_utf8, (unsigned char *)ans);

	add_msg_popup(ui, name_utf8, ans_utf8, true, winner_time);
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
