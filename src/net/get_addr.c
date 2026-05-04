#include <ifaddrs.h>
#include <arpa/inet.h>

int	get_my_addr(struct in_addr *addr)
{
    struct ifaddrs *ifaddr;

	if (getifaddrs(&ifaddr) == -1) {
		return (-1);
	}

	struct ifaddrs *ifa = ifaddr;
	while (ifa)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *sa = (struct sockaddr_in*)ifa->ifa_addr;
            if (sa->sin_addr.s_addr != htonl(INADDR_LOOPBACK)) // skip 127.0.0.1
            {
                *addr = sa->sin_addr;
                freeifaddrs(ifaddr);
                return (0);
            }
        }
		ifa = ifa->ifa_next;
	}

	freeifaddrs(ifaddr);
	return (-1);
}
