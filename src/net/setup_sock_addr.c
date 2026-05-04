#include "net/network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int setup_sock(int *sock)
{
	*sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (*sock == -1)
		return (-1);

	// make the socket non blockant
	if (fcntl(*sock, F_SETFL, O_NONBLOCK) == -1)
	{
		close(*sock);
		return (-1);
	}

	//setup for receiving
	int reuse = 1;
    setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(*sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		close(*sock);
		return (-1);
	}

    struct ip_mreq mreq;
    inet_pton(AF_INET, MULTICAST_ADDR, &mreq.imr_multiaddr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(*sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1)
	{
		close(*sock);
		return (-1);
	}

	// setup for multicast sending
	int ttl = 1;
	if (setsockopt(*sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) == -1)
	{
		close(*sock);
		return (-1);
	}

	return (0);
}

void	setup_multicast_addr(struct sockaddr_in *addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(PORT);
	inet_pton(AF_INET, MULTICAST_ADDR, &addr->sin_addr);
}

