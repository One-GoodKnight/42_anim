#include "net/state.h"
#include <string.h>
#include <stdio.h>

void	announce_hosting(int sock, struct sockaddr_in dest)
{
	char message[] = "HOSTING";
	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
}

void	send_answer(int sock, struct sockaddr_in dest, char *answer)
{
	char buff[256];
	snprintf(buff, sizeof(buff), "ANSWER:%s", answer);
	sendto(sock, buff, strlen(buff) + 1, 0, (struct sockaddr*)&dest, sizeof(dest));
}
