#ifndef ACTIONS_H
# define ACTIONS_H

# include "vector.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdbool.h>

int 	read_all_messages(int sock, t_vec *messages);

void	announce_hosting(int sock, struct sockaddr_in dest);
void	send_answer(int sock, struct sockaddr_in dest, char *answer);

#endif
