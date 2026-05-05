#include "net/network.h"
#include "net/state.h"
#include <string.h>
#include <stdio.h>

void	announce_hosting(t_net *net)
{
	if (time(NULL) == net->last_heartbeat_sent)
		return ;

	printf("I am the host\n");

	char message[] = "HOSTING";
	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
	
	net->last_heartbeat_sent = time(NULL);
}

void	announce_winner(t_net *net)
{
	char message[] = "WINNER: XXX won !";
	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
}

void	send_answer(int sock, struct sockaddr_in dest, char *answer)
{
	char buff[256];
	snprintf(buff, sizeof(buff), "ANSWER:%s", answer);
	sendto(sock, buff, strlen(buff) + 1, 0, (struct sockaddr*)&dest, sizeof(dest));
}
