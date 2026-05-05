#ifndef HANDLE_MSG_H
# define HANDLE_MSG_H

# include "logic/question.h"
# include "net/network.h"

void	process_msg_host(t_net *net, t_qst *qst);
void	process_msg_client(t_net *net);

#endif
