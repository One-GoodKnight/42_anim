#ifndef SETUP_SOCKETS_H
# define SETUP_SOCKETS_H

#include <netinet/in.h>

int setup_multicast_socket(int *sock, struct sockaddr_in *dest);
int	setup_unicast_socket(int *sock);

#endif
