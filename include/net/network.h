#ifndef NETWORK_H
# define NETWORK_H

# define MULTICAST_ADDR "239.74.74.74"
# define PORT 7474

# define NEXT_GAME_COOLDOWN 0
# define GAME_TIMEOUT 33

# define LISTENING_PHASE_DURATION 2
# define HOST_TIMEOUT 3

# define SEND_QUESTION_COOLDOWN 1.5f  // time between announce start and announce qst

# define HOST_BG_LOOP_NO_CLIENT_TIMEOUT 3

# include "net/state.h"
# include "vector.h"
# include <time.h>

typedef struct s_net
{
    t_net_state			state;

	struct in_addr		my_addr;

    int                 sock;
	struct sockaddr_in  multicast_addr;	// host to clients
	struct sockaddr_in  host_addr;		// client to host
	
	time_t				last_heartbeat_sent;  // host to client
	time_t				last_heartbeat_received;

	time_t				last_heartbeat_sent_playing;  // client to host
	time_t				last_heartbeat_received_playing;

	time_t				next_game_cd_sent;
	double				next_game_cooldown;

	// current game
	t_vec				messages;

	double				game_start;
	double				send_qst_cd;

	bool				game_ended;
}   t_net;

int		init_net(t_net *net);
void	reset_net_game_state(t_net *net);
void	clean_net(t_net *net);
void	set_to_host(t_net *net);
int		get_my_addr(struct in_addr *addr);

#endif
