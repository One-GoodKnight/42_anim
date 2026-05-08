#ifndef RENDER_UI_H
# define RENDER_UI_H

# include "ui/ui.h"
# include "window/input.h"
# include "raylib.h"

void	render_ui(t_ui *ui, char *qst, t_input *input, Font font, Font font_anim, Texture2D logo);
void	render_corners(t_ui *ui);
void	render_anim_text(t_ui *ui, Font font_anim);
void	render_input(t_ui *ui, char *qst, t_input *input, Font font);
void	render_msg_popups(t_ui *ui, Font font);

#endif
