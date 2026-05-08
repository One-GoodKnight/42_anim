#include "net/message.h"
#include "vector.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

int read_all_messages(int sock, t_vec *messages)
{
	t_msg msg;
	socklen_t sender_len;
	struct timespec	ts;

	sender_len = sizeof(msg.sender);
	int n = recvfrom(sock, msg.msg, sizeof(msg.msg) - 1, 0, (struct sockaddr*)&msg.sender, &sender_len);
	while (n != -1)
	{
		msg.msg[n] = '\0';

		clock_gettime(CLOCK_MONOTONIC, &ts);
		float time = ts.tv_sec;
		time += (int)(ts.tv_nsec / 10000000) / 100.0f;

		msg.time = time;

		if (vec_push(messages, &msg) == -1)
			return (-1);

		sender_len = sizeof(msg.sender);
		n = recvfrom(sock, msg.msg, sizeof(msg.msg) - 1, 0, (struct sockaddr*)&msg.sender, &sender_len);
	}

	if (errno != EAGAIN)
		return (-1);

	return (0);
}

