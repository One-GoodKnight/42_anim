#include "ui/render_ui/colors.h"
#include "ui/render_ui/render_ui.h"
#include "ui/ui.h"
#include "raylib.h"

static void	render_background(t_ui *ui)
{
	Color bg_color = (Color){BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 * ui->fade_progress};

	DrawRectangle(0, 0, ui->width, ui->height, bg_color);
}

static void	render_logo(t_ui *ui, Texture2D logo)
{
	int	x = ui->top_left_corner.org.x + ui->top_left_corner.offset.x;
	int	y = ui->top_left_corner.org.y + ui->top_left_corner.offset.y;

	x += 179;
	y -= 180;

	DrawTextureEx(logo, (Vector2){x, y}, 0.0f, 1.0f, WHITE);
}

static void	render_question(t_ui *ui, char *qst, Font font)
{
	int	text_width = MeasureTextEx(font, qst, (float)font.baseSize, FONT_SPACING).x;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	x = ui->width / 2 - text_width / 2;
	int	y = ui->height / 2 - text_height; // make the center y of the screen perfectly separate question and input
	y -= TEXT_Y_OFFSET;

	DrawTextEx(font, qst, (Vector2){x, y}, FONT_SIZE, FONT_SPACING, FONT_COLOR);
}

void	render_ui(t_ui *ui, char *qst, t_input *input)
{
	BeginDrawing();
	ClearBackground(BLANK);

	render_background(ui);
	render_corners(ui);
	render_logo(ui, ui->logo);
	render_anim_text(ui, ui->fonts.font_anim);

	render_msg_popups(ui, ui->fonts.font_popups);
	render_question(ui, qst, ui->fonts.font);
	render_input(ui, qst, input, ui->fonts.font);

	EndDrawing();
}
