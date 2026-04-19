#include "window/rendering/ui.h"

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
