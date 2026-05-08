#ifndef MESSAGES_H
# define MESSAGES_H

#include <netinet/in.h>

typedef struct	s_msg
{
	char				msg[256];
	struct sockaddr_in	sender;
	float				time;
}	t_msg;

#endif
