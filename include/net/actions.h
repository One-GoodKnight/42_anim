#ifndef ACTIONS_H
# define ACTIONS_H

# include "net/network.h"
# include "vector.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdbool.h>

int 	read_all_messages(int sock, t_vec *messages);

void	announce_hosting(t_net *net);
void	announce_start(t_net *net);
void	announce_question(t_net *net, char *qst);
void	announce_winner(t_net *net, char *name, char *ans);
void	announce_attempt(t_net *net, char *name, char *ans);
void	announce_timeout(t_net *net, char *ans);
void	announce_next_game_cd(t_net *net);

void	send_answer(int sock, struct sockaddr_in dest, char *answer);
void	send_playing(t_net *net);

#endif
