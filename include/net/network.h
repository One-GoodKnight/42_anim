#ifndef NETWORK_H
# define NETWORK_H

# define MULTICAST_ADDR "239.74.74.74"
# define PORT 7474

# define HOST_HEARTBEAT_DELAY 1

# include "net/state.h"
# include "vector.h"
# include <time.h>

typedef struct s_net
{
    t_state             state;

	struct in_addr		my_addr;

    int                 sock;
	struct sockaddr_in  multicast_addr;	// host to clients
	struct sockaddr_in  host_addr;		// client to host
	
	t_vec				messages;

	time_t				last_heartbeat_sent;
	time_t				last_heartbear_received;
}   t_net;

int		setup_net(t_net *net);
void	clean_net(t_net *net);
int		get_my_addr(struct in_addr *addr);

#endif
