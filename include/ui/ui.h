#ifndef UI_H
# define UI_H

# include "ui/corner.h"
# include "vector.h"

# define FONT_SIZE 32
# define FONT_SPACING 0

# define FONT_SIZE_ANIM_TEXT 80

# define BOX_WIDTH 1000
# define BOX_HEIGHT 600

# define BORDER_THICKNESS 4

# define TEXT_Y_OFFSET 30

# define RESULT_SCREEN_TIME 3

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

	float		time_question_popped;

	float		result_screen_time_left;

	t_vec		messages_popups;
}	t_ui;

void	init_ui(t_ui *ui);

#endif
