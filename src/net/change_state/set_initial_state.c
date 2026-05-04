#include "net/network.h"
#include "net/setup_sockets.h"
#include "net/actions.h"

int	set_initial_state(t_net *net)
{
	bool found;

	if (listen_for_host(net->multicast_sock, &found, &net->host_addr, LISTENING_DURATION) == -1)
		return (-1);
	if (found)
	{
		if (setup_unicast_socket(&net->host_sock) == -1)
			return (-1);
		net->state = CLIENT;
	}
	else
		net->state = HOST;
	return (0);
}
