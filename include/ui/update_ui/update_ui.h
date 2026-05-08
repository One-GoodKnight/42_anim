#ifndef UPDATE_UI_H
# define UPDATE_UI_H

# include "ui/update_ui/pid_controller.h"
# include "ui/ui.h"
# include <stdbool.h>

# define FADE_SPEED 10

void	update_ui(t_ui *ui, t_pid_controller *pid);
void	apply_pid_controller(t_ui *ui, t_pid_controller pid);
void	floating_corners(t_ui *ui);

void	add_msg_popup(t_ui *ui, char *name, char *msg, bool winner, float win_time);
void	update_msg_popups(t_ui *ui);

#endif
