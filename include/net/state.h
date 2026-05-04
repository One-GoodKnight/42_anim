#ifndef STATES_H
# define STATES_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdbool.h>

# define LISTENING_PHASE_DURATION 5

typedef struct s_net t_net;

typedef enum e_state
{
	LISTENING,
	HOST,
	CLIENT,
} t_state;

int		set_initial_state(t_net *net);
void	handle_conflicts(t_net *net);

#endif
