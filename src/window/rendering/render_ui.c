#include "window/rendering/ui.h"
#include "raylib.h"
#include "window/rendering/colors.h"

static void fade(t_ui *ui)
{
	ui->fade_progress += ui->dt * FADE_SPEED;

	if (ui->fade_progress >= 1)
	{
		ui->fade_progress = 1;
		ui->state = BRING_BORDERS;
	}
}

static void	render_background(t_ui *ui)
{
	Color bg_color = (Color){BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 * ui->fade_progress};

	DrawRectangle(0, 0, ui->width, ui->height, bg_color);
}

static void	render_logo(t_ui *ui, Texture2D logo)
{
	int	x = ui->top_left_corner.org_x;
	int	y = ui->top_left_corner.org_y;

	x += 180;
	y -= 180;

	DrawTextureEx(logo, (Vector2){x, y}, 0.0f, 1.0f, WHITE);
}

void	render_ui(t_ui *ui, t_qst *qst, t_input *input, Font font, Texture2D logo)
{
	ui->dt = GetFrameTime();

	if (ui->state == BACKGROUND_FADE)
		fade(ui);

	BeginDrawing();
	ClearBackground(BLANK);

	render_background(ui);
	render_logo(ui, logo);
	render_corners(ui);

	render_input(input, 200, 200, font);

	EndDrawing();
}
