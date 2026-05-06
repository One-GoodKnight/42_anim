#ifndef UI_H
# define UI_H

#include "raylib.h"
#include "window/rendering/corner.h"
#include "window/input.h"
#include "game/question.h"

# define FONT_SIZE 32
# define FONT_SPACING 0

# define FADE_SPEED 10

# define BOX_WIDTH 1000
# define BOX_HEIGHT 600

typedef enum e_ui_state
{
	BACKGROUND_FADE,
	BRING_BORDERS,
	SHOW_TEXT,
	COMPLETE,
}	t_ui_state;

typedef struct s_ui
{
	int			width;
	int			height;

	float		dt;

	t_ui_state	state;

	float 		fade_progress;

	t_corner	top_left_corner;
	t_corner	top_right_corner;
	t_corner	bottom_right_corner;
	t_corner	bottom_left_corner;
}	t_ui;

void	render_ui(t_ui *ui, t_qst *qst, t_input *input, Font font, Texture2D logo);
void	render_corners(t_ui *ui);
void	render_input(t_input *input, int x, int y, Font font);

#endif
