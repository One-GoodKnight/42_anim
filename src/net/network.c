#include "net/message.h"
#include "net/network.h"
#include "net/setup_sock_addr.h"
#include <arpa/inet.h>
#include <float.h>

void	reset_net_game_state(t_net *net)
{
	vec_clear(&net->messages);
	net->game_start = DBL_MAX;
	net->send_qst_cd = SEND_QUESTION_COOLDOWN;
	net->game_ended = false;
}

int	init_net(t_net *net)
{
	vec_init(&net->messages, sizeof(t_msg), NULL);

	if (get_my_addr(&net->my_addr) == -1)
		return (-1);

	if (setup_sock(&net->sock) == -1)
		return (-1);
	setup_multicast_addr(&net->multicast_addr);

	if (set_initial_state(net) == -1)
	{
		clean_net(net);
		return (-1);
	}

	net->next_game_cd_sent = 0;
	net->next_game_cooldown = 0;

	net->game_start = DBL_MAX;
	net->send_qst_cd = 0;

	net->last_heartbeat_sent = 0;
	net->last_heartbeat_received = time(NULL);

	net->last_heartbeat_sent_playing = 0;
	net->last_heartbeat_received_playing = time(NULL);

	reset_net_game_state(net);

	return (0);
}

void	clean_net(t_net *net)
{
	if (!net)
		return ;
	if (net->sock != -1)
	{
		close(net->sock);
		net->sock = -1;
	}

	vec_free(&net->messages);
}

void	set_to_host(t_net *net)
{
	net->state = HOST;
	inet_pton(AF_INET, "127.0.0.1", &net->host_addr.sin_addr);
	net->host_addr.sin_port = htons(PORT);
	net->host_addr.sin_family = AF_INET;
}
