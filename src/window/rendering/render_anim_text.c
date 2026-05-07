#include "window/rendering/colors.h"
#include "window/rendering/ui.h"

void	render_anim_text(t_ui *ui, Font font_anim)
{
	char text[] = "Anim";

	int	x = ui->bottom_right_corner.org_x + ui->bottom_right_corner.x_offset;
	int	y = ui->bottom_right_corner.org_y + ui->bottom_right_corner.y_offset;

	int	text_width = MeasureTextEx(font_anim, text, (float)font_anim.baseSize, FONT_SPACING).x;
	int	text_height = MeasureTextEx(font_anim, "|", (float)font_anim.baseSize, FONT_SPACING).y;

	x = x - text_width - 207;
	y = y - text_height + 8;

	DrawTextEx(font_anim, text, (Vector2){x, y}, FONT_SIZE_ANIM_TEXT, FONT_SPACING, FONT_COLOR);
}
