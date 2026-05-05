#include "net/message.h"
#include "net/network.h"
#include <string.h>
#include <stdio.h>

static void	process_hosting(t_net *net, t_msg *msg)
{
	(void)net;
	if (strncmp(msg->msg, "HOSTING", strlen("HOSTING")) != 0)
		return ;

	printf("Received host heartbeat\n");
}

static void	process_winner(t_net *net, t_msg *msg)
{
	(void)net;
	if (strncmp(msg->msg, "WINNER:", strlen("WINNER:")) != 0)
		return ;

	printf("%s\n", msg->msg);
}

void	process_msg_client(t_net *net)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		process_hosting(net, msg);
		process_winner(net, msg);
	}
}
