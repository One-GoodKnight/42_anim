#include "net/actions.h"
#include "net/network.h"
#include "net/process_msg.h"
#include "net/state.h"

int host_bg_loop(t_net *net, t_qst *qst)
{
	if (net->state != HOST)
		return (0);

	while (1)
	{
		if (net->winner_message_sent == true)
			return (0);

		if (read_all_messages(net->sock, &net->messages) == -1)
			return (-1);
		handle_conflicts(net, NULL);

		if (net->state == HOST)
		{
			announce_hosting(net);
			process_msg_host(net, qst);
		}

		usleep(0.016 * 1000000);
	}

	return (0);
}
