#include "net/message.h"
#include "net/network.h"
#include "net/setup_sock_addr.h"

int	init_net(t_net *net)
{
	vec_init(&net->messages, sizeof(t_msg), NULL);

	if (get_my_addr(&net->my_addr) == -1)
		return (-1);

	if (setup_sock(&net->sock) == -1)
		return (-1);
	setup_multicast_addr(&net->multicast_addr);

	if (set_initial_state(net) == -1)
	{
		clean_net(net);
		return (-1);
	}

	return (0);
}

void	clean_net(t_net *net)
{
	if (!net)
		return ;
	if (net->sock != -1)
	{
		close(net->sock);
		net->sock = -1;
	}

	vec_free(&net->messages);
}
