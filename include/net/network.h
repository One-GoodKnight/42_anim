#ifndef NETWORK_H
# define NETWORK_H

# define PORT 7474

# include "net/state.h"
# include "vector.h"

typedef struct s_net
{
    t_state             state;

	struct in_addr		my_addr;

    int                 sock;
	struct sockaddr_in  multicast_addr;	// host to clients
	struct sockaddr_in  host_addr;		// client to host
	
	t_vec				messages;
}   t_net;

int		setup_net(t_net *net);
void	clean_net(t_net *net);
int		get_my_addr(struct in_addr *addr);

#endif
