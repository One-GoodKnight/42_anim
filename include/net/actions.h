#ifndef ACTIONS_H
# define ACTIONS_H

# include "vector.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdbool.h>

void	announce_hosting(int sock, struct sockaddr_in dest);
int 	read_all_messages(int sock, t_vec *messages);
//int 	listen_for_host(int sock, bool *found, struct sockaddr_in *host_addr, int duration);

#endif
