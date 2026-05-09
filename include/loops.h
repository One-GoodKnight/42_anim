#ifndef LOOPS_H
# define LOOPS_H

# include "file_op/data.h"
# include "net/network.h"
# include "game/game.h"
# include "game/question.h"

int		lobby_loop(t_data *data, t_net *net, t_qst *qst, t_game *game);
int		game_loop(t_net *net, t_qst *qst, t_game *game);

void	host_loop_helper(t_net *net, t_qst *qst, float dt);
int 	host_bg_loop(t_net *net, t_qst *qst);

#endif
