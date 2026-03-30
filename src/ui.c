#include "ui.h"

void	init_line(t_line *line, int width, int height, Color color, int trail)
{
	line->width = width;
	line->height = height;
	line->color = color;
	line->trail = trail;
}

void	draw_line(int x, int y, t_line line)
{
	DrawRectangle(x, y, line.width, line.height, line.color);
	if (!line.trail)
		return ;
	for (int i = 0; i < line.trail; i++){
		Color transparent_color = line.color;
		transparent_color.a = 255 - (int)(((float)i / (float)line.trail) * 255);
		DrawRectangle(x + line.width + i, y, 1, line.height, transparent_color);
	}
}

void	draw_box(int x, int y, t_line line, int height, Color color, bool fade)
{
	t_line middle_line = line;
	middle_line.width -= line.height * 2;
	if (fade)
		middle_line.width *= 0.9;
	middle_line.height = height;
	middle_line.color = color;

	t_line vertical_line = line;
	vertical_line.height = height;
	vertical_line.width = line.height;
	vertical_line.trail = 0;

	draw_line(x - line.height, y - line.height, line);
	draw_line(x - line.height, y + height, line);
	draw_line(x - vertical_line.width, y, vertical_line);
	if (!fade)
		draw_line(x - vertical_line.width * 2 + line.width, y, vertical_line);

	draw_line(x, y, middle_line);
}

void	render_ui(t_qst *qst, t_input *input, Font font)
{
	BeginDrawing();
	ClearBackground(BLANK);

	//target
	t_line target_line;
	init_line(&target_line, 550, 4, TARGET_OUTLINE_BOX, 0);
	draw_box(10, 10, target_line, 60, TARGET_FILL_BOX, false);
	DrawTextEx(font, qst->data.qst.utf8, (Vector2){28, 27}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);

	//input_field
	t_line input_field_line;
	init_line(&input_field_line, 500, 4, INPUT_OUTLINE_BOX, 150);
	draw_box(100, 120, input_field_line, 60, INPUT_FILL_BOX, true);
	render_input(input, 120, 138, font);

	//link
	DrawRectangleGradientV(400, 73, 4, 45, TARGET_OUTLINE_BOX, INPUT_OUTLINE_BOX);

	EndDrawing();
}
