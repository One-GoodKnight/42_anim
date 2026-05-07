#ifndef MSG_POPUP_H
# define MSG_POPUP_H

# include <stdbool.h>

# define WINNER_TTL 3
# define STD_TTL	1

typedef struct	s_msg_popup
{
	char				name[256];
	char				msg[256];

	bool				winner;
	float				win_time;

	int					x;
	int					y;

	float				ttl;  // time to live
}	t_msg_popup;

#endif
