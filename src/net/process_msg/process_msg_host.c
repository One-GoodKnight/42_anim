#include "game/check_win.h"
#include "game/question.h"
#include "net/message.h"
#include "net/network.h"
#include "net/actions.h"
#include <string.h>
#include <stdio.h>

static void	process_answer(t_net *net, t_msg *msg, t_qst *qst)
{
	(void)net;
	if (strncmp(msg->msg, "ANSWER:", strlen("ANSWER:")) != 0)
		return ;

	if (check_win(msg->msg + strlen("ANSWER:"), qst))
		announce_winner(net);
	//printf("Received '%s'\n", msg->msg);
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
