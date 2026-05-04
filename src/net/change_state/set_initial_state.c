#include "net/message.h"
#include "net/network.h"
#include "net/setup_sock_addr.h"
#include "net/actions.h"
#include <time.h>
#include <string.h>

int	set_initial_state(t_net *net)
{
	time_t endtime = time(NULL) + LISTENING_PHASE_DURATION;

	net->state = HOST;
	while (time(NULL) < endtime)
	{
		if (read_all_messages(net->sock, &net->messages) == -1)
		{
			clean_net(net);
			return (-1);
		}

		int i = 0;
		while (i < net->messages.size)
		{
			t_msg *msg = vec_get(&net->messages, i);
			if (strncmp(msg->msg, "HOSTING", sizeof("HOSTING") - 1) == 0)
			{
				net->state = CLIENT;
				net->host_addr = msg->sender;
				net->host_addr.sin_port = htons(PORT);
				vec_clear(&net->messages);
				return (0);
			}
			i++;
		}

		vec_clear(&net->messages);
		sleep(1);
	}

	return (0);
}
