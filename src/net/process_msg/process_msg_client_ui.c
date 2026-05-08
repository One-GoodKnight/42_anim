#include "game/game.h"
#include "net/message.h"
#include "net/network.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "utils/utf8.h"
#include "utils/utils.h"
#include <string.h>

static int helper_winner_or_attempt(char *msg, char name_utf8[512], char ans_utf8[512])
{
	char *payload = msg;

	char *separator = strchr(payload, '|');
	if (!separator)
		return (-1);

	char name[256];
	int name_len = separator - payload;
	strncpy(name, payload, name_len);
	name[name_len] = '\0';

	char *ans = separator + 1;

	latin1_to_utf8((unsigned char *)name_utf8, (unsigned char *)name);
	latin1_to_utf8((unsigned char *)ans_utf8, (unsigned char *)ans);

	return (0);
}

static void	process_winner(t_ui *ui, t_msg *msg, t_game *game)
{
	char name_utf8[512];
	char ans_utf8[512];

	if (strncmp(msg->msg, "WINNER:", strlen("WINNER:")) != 0)
		return ;

	if (helper_winner_or_attempt(msg->msg + strlen("WINNER:"), name_utf8, ans_utf8) == -1)
		return ;

	float winner_time = get_time() - ui->time_question_popped;
	
	add_msg_popup(ui, name_utf8, ans_utf8, true, winner_time);
	game->state = RESULTS;
}

static void process_attempt(t_ui *ui, t_msg *msg)
{
	char name_utf8[512];
	char ans_utf8[512];

	if (strncmp(msg->msg, "ATTEMPT:", strlen("ATTEMPT:")) != 0)
		return ;

	if (helper_winner_or_attempt(msg->msg + strlen("ATTEMPT:"), name_utf8, ans_utf8) == -1)
		return ;

	add_msg_popup(ui, name_utf8, ans_utf8, false, 0.0f);
}

void	process_msg_client_ui(t_net *net, t_ui *ui, t_game *game)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_winner(ui, msg, game);
		process_attempt(ui, msg);
	}
}
