#ifndef STATES_H
# define STATES_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_net t_net;
typedef struct s_game t_game;

typedef enum e_net_state
{
	LISTENING,
	HOST,
	CLIENT,
} t_net_state;

int		set_initial_state(t_net *net);
void	handle_conflicts(t_net *net, t_game *game);

#endif
