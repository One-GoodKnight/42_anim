#ifndef MSG_POPUP_H
# define MSG_POPUP_H

# include <stdbool.h>

# define WINNER_TTL 999
# define STD_TTL	2

# define MIN_DIST_CENTER_X 350
# define MIN_DIST_CENTER_Y 250
# define MIN_DIST_EDGE 250

# define POPUP_SPEED 5

# define POPUP_BORDER_OFFSET 6
# define POPUP_BORDER_THICKNESS 2

# define SEPARATION_HEADER_MSG 3

typedef struct	s_msg_popup
{
	char				name[256];
	char				msg[256];

	bool				winner;
	float				win_time;

	int 				width;
	int					height;

	float				x;
	float				y;

	float				ttl;  // time to live
	bool				dead;
}	t_msg_popup;

#endif
