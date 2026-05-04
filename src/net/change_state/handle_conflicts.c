#include "net/message.h"
#include "net/network.h"
#include "string.h"

void	handle_conflicts(t_net *net)
{
	int i = 0;
	while (i < net->messages.size)
	{
		t_msg *msg = vec_get(&net->messages, i++);
		if (strncmp(msg->msg, "HOSTING", strlen("HOSTING")) != 0)
			continue ;

		if (msg->sender.sin_addr.s_addr < net->my_addr.s_addr)
		{
			if (net->state == CLIENT && msg->sender.sin_addr.s_addr > net->host_addr.sin_addr.s_addr)
				continue ;

			net->host_addr = msg->sender;
			net->host_addr.sin_port = htons(PORT);
			net->state = CLIENT;
		}
	}
}
