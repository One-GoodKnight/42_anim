#include "net/network.h"
#include "net/setup_sockets.h"

int	setup_net(t_net *net)
{
	if (get_my_addr(&net->my_addr) == -1)
		return (-1);

	if (setup_multicast_socket(&net->multicast_sock, &net->multicast_addr) == -1)
		return (-1);

	if (set_initial_state(net) == -1)
	{
		clean_net(net);
		return (-1);
	}
	return (0);
}

void	clean_net(t_net *net)
{
	if (net->multicast_sock != -1)
	{
		close(net->multicast_sock);
		net->multicast_sock = -1;
	}
	if (net->host_sock != -1)
	{
		close(net->host_sock);
		net->host_sock = -1;
	}
}
