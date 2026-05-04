#include "net/network.h"
#include "net/actions.h"
#include "net/setup_sockets.h"
#include "stdio.h"

int	handle_conflicts(t_net *net)
{
	uint32_t			lowest_addr = net->my_addr.s_addr;
	struct sockaddr_in	host_addr;
	bool 				found;

	if (listen_for_host(net->multicast_sock, &found, &host_addr, 0) == -1)
		return (-1);

	while (found)
	{
		if (host_addr.sin_addr.s_addr < lowest_addr)
		{
			lowest_addr = host_addr.sin_addr.s_addr;
			// set new host addr here, open host socket later
			net->host_addr = host_addr;
		}

		if (listen_for_host(net->multicast_sock, &found, &host_addr, 0) == -1)
			return (-1);
	}

	// downgrading from host to client
	if (lowest_addr != net->my_addr.s_addr)
	{
		printf("Conflict ! downgrading to client\n");
		if (setup_unicast_socket(&net->host_sock) == -1)
			return (-1);
		net->state = CLIENT;
	}
	return (0);
}
