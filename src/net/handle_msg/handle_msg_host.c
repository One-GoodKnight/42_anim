#include "net/message.h"
#include "net/network.h"
#include <string.h>
#include <stdio.h>

static void	handle_answer(t_net *net, t_msg *msg)
{
	(void)net;
	if (strncmp(msg->msg, "ANSWER", strlen("ANSWER")) != 0)
		return ;

	printf("Received %s !\n", msg->msg);
}

void	handle_msg_host(t_net *net)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		handle_answer(net, msg);
	}
}
