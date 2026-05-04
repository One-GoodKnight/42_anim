#ifndef SETUP_SOCKETS_H
# define SETUP_SOCKETS_H

#include <netinet/in.h>

int		setup_sock(int *sock);
void	setup_multicast_addr(struct sockaddr_in *addr);

#endif
