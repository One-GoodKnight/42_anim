#ifndef UI_H
# define UI_H

#include "raylib.h"
#include "input.h"
#include "question.h"

# define TARGET_OUTLINE_BOX (Color){255, 105, 180, 255}
# define TARGET_FILL_BOX (Color){156, 0, 99, 255}

# define INPUT_OUTLINE_BOX (Color){0, 128, 255, 255}
# define INPUT_FILL_BOX (Color){0, 0, 64, 255}

# define FONT_COLOR RAYWHITE
# define FONT_SIZE 32
# define FONT_SPACING 0

typedef struct s_line
{
	int width;
	int height;
	Color color;
	int trail;
}	t_line;

void	render_ui(t_qst *qst, t_input *input, Font font);

#endif
