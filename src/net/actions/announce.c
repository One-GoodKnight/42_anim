#include "net/state.h"

void	announce_hosting(int sock, struct sockaddr_in dest)
{
	char message[] = "HOSTING";
	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
}
