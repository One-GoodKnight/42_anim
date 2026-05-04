#ifndef NETWORK_H
# define NETWORK_H

# include "net/state.h"

typedef struct s_net
{
    t_state             state;

	struct in_addr		my_addr;

    int                 multicast_sock; // for discovery (LISTENING/ANNOUNCING)
	struct sockaddr_in  multicast_addr; // multicast addr

    int                 host_sock;      // unicast socket to talk to host
	struct sockaddr_in  host_addr;		// host's addr

}   t_net;

/*
typedef struct s_net
{
    t_state             state;

    struct in_addr      my_addr;

    int                 hosting_sock;
    struct sockaddr_in  hosting_addr;

    int                 game_sock;
    struct sockaddr_in  game_addr;
    struct sockaddr_in  host_addr;
}   t_net;
*/

int		setup_net(t_net *net);
void	clean_net(t_net *net);
int		get_my_addr(struct in_addr *addr);

#endif
