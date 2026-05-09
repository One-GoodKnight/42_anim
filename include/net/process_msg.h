#ifndef HANDLE_MSG_H
# define HANDLE_MSG_H

# include "game/game.h"
# include "game/question.h"
# include "ui/ui.h"
# include "net/network.h"
# include "window/input.h"

void	process_msg_host(t_net *net, t_qst *qst);
void	process_msg_client(t_net *net, t_game *game);
void	process_msg_client_ui(t_net *net, t_ui *ui, t_game *game, t_input *input);

#endif
