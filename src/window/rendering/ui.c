#include "window/rendering/ui.h"

void	render_ui(t_qst *qst, t_input *input, Font font)
{
	BeginDrawing();
	ClearBackground(BLANK);

	//target
	t_line target_line;
	init_line(&target_line, 550, 4, TARGET_OUTLINE_BOX, 0);
	draw_box(10, 10, target_line, 60, TARGET_FILL_BOX, false);
	DrawTextEx(font, (char *)qst->data.qst.utf8, (Vector2){28, 27}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);

	//input_field
	t_line input_field_line;
	init_line(&input_field_line, 500, 4, INPUT_OUTLINE_BOX, 150);
	draw_box(100, 120, input_field_line, 60, INPUT_FILL_BOX, true);
	render_input(input, 120, 138, font);

	//link
	DrawRectangleGradientV(400, 73, 4, 45, TARGET_OUTLINE_BOX, INPUT_OUTLINE_BOX);

	EndDrawing();
}
