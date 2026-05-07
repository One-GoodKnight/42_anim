#ifndef HANDLE_MSG_H
# define HANDLE_MSG_H

# include "game/game.h"
# include "game/question.h"
# include "net/network.h"

void	process_msg_host(t_net *net, t_qst *qst);
void	process_msg_client(t_net *net, t_game *game);

#endif
