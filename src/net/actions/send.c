#include "net/network.h"
#include "net/state.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

// HOST

void	announce_hosting(t_net *net)
{
	if (time(NULL) == net->last_heartbeat_sent)
		return ;

	char message[] = "HOSTING";
	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
	
	net->last_heartbeat_sent = time(NULL);
	printf("I am the host\n");
}

void	announce_winner(t_net *net, char *name, char *ans)
{
	char message [256];
	snprintf(message, sizeof(message), "WINNER:%s|%s", name, ans);

	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
	net->game_ended = true;
	net->next_game_cooldown = NEXT_GAME_COOLDOWN;
	printf("Winner announced\n");
}

void	announce_attempt(t_net *net, char *name, char *ans)
{
	char message [256];
	snprintf(message, sizeof(message), "ATTEMPT:%s|%s", name, ans);

	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
}

void	announce_timeout(t_net *net, char *ans)
{
	char message [256];
	snprintf(message, sizeof(message), "TIMEOUT:%s", ans);

	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
	net->game_ended = true;  // stop processing answers
	net->next_game_cooldown = NEXT_GAME_COOLDOWN;
	printf("Timeout announced\n");
}

void	announce_next_game_cd(t_net *net)
{
	char message [256];
	snprintf(message, sizeof(message), "NEXT_GAME_CD:%f", net->next_game_cooldown);

	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
}

void	announce_start(t_net *net)
{
	char message[] = "STARTING";
	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&dest, sizeof(dest));
	printf("Start announced\n");
}

void	announce_question(t_net *net, char *qst)
{
	char buff[256];
	snprintf(buff, sizeof(buff), "QUESTION:%s", qst);

	int sock = net->sock;
	struct sockaddr_in dest = net->multicast_addr;

	sendto(sock, buff, strlen(buff) + 1, 0, (struct sockaddr*)&dest, sizeof(dest));
	net->game_start = time(NULL);
	printf("Question announced\n");
}


// CLIENT

void	send_answer(int sock, struct sockaddr_in dest, char *answer)
{
	char buff[256];

	int	uid = getuid();
	struct passwd *passwd = getpwuid(uid);
	if (!passwd)
		return ;

	snprintf(buff, sizeof(buff), "ANSWER:%s|%s", passwd->pw_name, answer);
	sendto(sock, buff, strlen(buff) + 1, 0, (struct sockaddr*)&dest, sizeof(dest));
}

void	send_playing(t_net *net)
{
	if (net->last_heartbeat_sent_playing == time(NULL))
		return ;

	char message[] = "PLAYING";
	struct sockaddr_in dest = net->host_addr;

	sendto(net->sock, message, strlen(message) + 1, 0, (struct sockaddr*)&dest, sizeof(dest));
	net->last_heartbeat_sent_playing = time(NULL);
}
