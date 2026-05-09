#include "game/game.h"
#include "game/question.h"
#include "net/message.h"
#include "net/network.h"
#include "net/actions.h"
#include <string.h>

static void	process_answer(t_net *net, t_msg *msg, t_qst *qst)
{
	if (strncmp(msg->msg, "ANSWER:", strlen("ANSWER:")) != 0)
		return ;

	char *payload = msg->msg + strlen("ANSWER:");

	char *separator = strchr(payload, '|');
	if (!separator)
		return ;

	char name[256];
	int name_len = separator - payload;
	strncpy(name, payload, name_len);
	name[name_len] = '\0';

	char *ans = separator + 1;

	if (net->winner_message_sent == false && check_win(ans, qst))
		announce_winner(net, name, ans);
	else
		announce_attempt(net, name, ans);
}

void	process_msg_host(t_net *net, t_qst *qst)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_answer(net, msg, qst);
	}
}
