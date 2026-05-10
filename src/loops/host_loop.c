#include "game/question.h"
#include "net/actions.h"
#include "net/network.h"
#include "net/process_msg.h"
#include "net/state.h"
#include <stdio.h>

static void tick_qst(t_net *net, t_qst *qst, float dt)
{
	if (net->send_qst_cd <= 0)
		return ;

	net->send_qst_cd -= dt;
	if (net->send_qst_cd <= 0)
		announce_question(net, (char *)qst->data.qst.utf8);
}

static void	check_game_timeout(t_net *net, t_qst *qst)
{
	if (net->game_ended == true)
		return ;

	if (time(NULL) - net->game_start >= GAME_TIMEOUT)
		announce_timeout(net, (char *)qst->data.qst.ans);
}

void	host_loop_helper(t_net *net, t_qst *qst, float dt)
{
	handle_conflicts(net);
	announce_hosting(net);
	process_msg_host(net, qst);
	tick_qst(net, qst, dt);
	check_game_timeout(net, qst);
}

static bool	clients_playing(t_net *net)
{
	if (time(NULL) - net->last_heartbeat_received_playing >= HOST_BG_LOOP_NO_CLIENT_TIMEOUT)
		return (false);

	return (true);
}

int host_bg_loop(t_net *net, t_qst *qst)
{
	if (net->state != HOST)
		return (0);

	while (net->game_ended == false && clients_playing(net))
	{
		if (read_all_messages(net->sock, &net->messages) == -1)
			return (-1);

		host_loop_helper(net, qst, 0.016f);

		vec_clear(&net->messages);
		
		usleep(0.016f * 1000000);
	}

	return (0);
}
