#ifndef ACTIONS_H
# define ACTIONS_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <stdbool.h>

void	announce_hosting(int sock, struct sockaddr_in dest);
int 	listen_for_host(int sock, bool *found, struct sockaddr_in *host_addr, int duration);

#endif
