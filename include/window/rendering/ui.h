#ifndef UI_H
# define UI_H

#include "raylib.h"
#include "window/input.h"
#include "logic/question.h"
#include "window/rendering/colors.h"

# define TARGET_OUTLINE_BOX LIGHT_PINK
# define TARGET_FILL_BOX DARK_PINK

# define INPUT_OUTLINE_BOX LIGHT_NAVY
# define INPUT_FILL_BOX DARK_NAVY

# define FONT_SIZE 32
# define FONT_SPACING 0

typedef struct s_line
{
	int width;
	int height;
	Color color;
	int trail;
}	t_line;

void	draw_box(int x, int y, t_line line, int height, Color color, bool fade);
void	init_line(t_line *line, int width, int height, Color color, int trail);
void	render_ui(t_qst *qst, t_input *input, Font font);

#endif
