#ifndef UPDATE_UI_H
# define UPDATE_UI_H

# include "ui/update_ui/pid_controller.h"
# include "ui/ui.h"

# define FADE_SPEED 10

void	update_ui(t_ui *ui, t_pid_controller *pid_controller);
void	apply_pid_controller(t_ui *ui);
void	floating_corners(t_ui *ui);

#endif
