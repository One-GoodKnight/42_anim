#include "net/message.h"
#include "vector.h"
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

int read_all_messages(int sock, t_vec *messages)
{
	t_msg msg;
	socklen_t sender_len;

	sender_len = sizeof(msg.sender);
	int n = recvfrom(sock, msg.msg, sizeof(msg.msg) - 1, 0, (struct sockaddr*)&msg.sender, &sender_len);
	while (n != -1)
	{
		msg.msg[n] = '\0';
		if (vec_push(messages, &msg) == -1)
			return (-1);

		sender_len = sizeof(msg.sender);
		n = recvfrom(sock, msg.msg, sizeof(msg.msg) - 1, 0, (struct sockaddr*)&msg.sender, &sender_len);
	}

	if (errno != EAGAIN)
		return (-1);

	return (0);
}

/*
int listen_for_host(int sock, bool *found, struct sockaddr_in *host_addr, int duration)
{
	struct sockaddr_in sender_addr;
	socklen_t sender_len = sizeof(sender_addr);
	char buf[256];

	time_t endtime = time(NULL) + duration;
	*found = false;
	while (time(NULL) <= endtime)
	{
		int n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&sender_addr, &sender_len);
		while (n != -1)
		{
			buf[n] = '\0';
			if (strcmp(buf, "HOSTING") == 0)
			{
				*found = true;
				*host_addr = sender_addr;
				return (0);
			}
			buf[0] = '\0';

			n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&sender_addr, &sender_len);
		}

		if (errno == EAGAIN)
		{
			// if duration is 0, don't sleep at all
			if (duration == 0)
				return (0);
			sleep(1);
			continue;
		}
		return (-1);
	}
	
	return (0);
}
*/
