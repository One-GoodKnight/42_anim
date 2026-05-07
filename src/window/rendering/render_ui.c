#include "window/rendering/corner.h"
#include "window/rendering/ui.h"
#include "raylib.h"
#include "window/rendering/colors.h"
#include <time.h>
#include <math.h>

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

static void	compute_floating_offset(t_corner *corner, struct timespec ts)
{
	float	t = ts.tv_sec + ts.tv_nsec * 1e-9;

	corner->x_offset = cosf(corner->phase + t * FLOATING_FREQUENCY_1) * FLOATING_AMPLITUDE_1;
	corner->x_offset += cosf(corner->phase * 1.25f + t * FLOATING_FREQUENCY_2) * FLOATING_AMPLITUDE_2;
	corner->x_offset += cosf(corner->phase * 1.75f + t * FLOATING_FREQUENCY_3) * FLOATING_AMPLITUDE_3;

	corner->y_offset = sinf(corner->phase + t * FLOATING_FREQUENCY_1) * FLOATING_AMPLITUDE_1;
	corner->y_offset += sinf(corner->phase * 0.75f + t * FLOATING_FREQUENCY_2) * FLOATING_AMPLITUDE_2;
	corner->y_offset += sinf(corner->phase * 0.25f + t * FLOATING_FREQUENCY_3) * FLOATING_AMPLITUDE_3;
}

static void	floating_corners(t_ui *ui)
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	compute_floating_offset(&ui->top_left_corner, ts);
	compute_floating_offset(&ui->top_right_corner, ts);
	compute_floating_offset(&ui->bottom_right_corner, ts);
	compute_floating_offset(&ui->bottom_left_corner, ts);
}

static void	render_logo(t_ui *ui, Texture2D logo)
{
	int	x = ui->top_left_corner.org_x + ui->top_left_corner.x_offset;
	int	y = ui->top_left_corner.org_y + ui->top_left_corner.y_offset;

	x += 180;
	y -= 180;

	DrawTextureEx(logo, (Vector2){x, y}, 0.0f, 1.0f, WHITE);
}

static void	render_question(t_ui *ui, t_qst *qst, Font font)
{
	char *text = (char *)qst->data.qst.utf8;

	int	text_width = MeasureTextEx(font, text, (float)font.baseSize, FONT_SPACING).x;
	int	text_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;

	int	x = ui->width / 2 - text_width / 2;
	int	y = ui->height / 2 - text_height; // make the center y of the screen perfectly separate question and input
	y -= TEXT_Y_OFFSET;

	DrawTextEx(font, text, (Vector2){x, y}, FONT_SIZE, FONT_SPACING, FONT_COLOR);
}

void	render_ui(t_ui *ui, t_qst *qst, t_input *input, Font font, Texture2D logo)
{
	ui->dt = GetFrameTime();

	if (ui->state == BACKGROUND_FADE)
		fade(ui);

	floating_corners(ui);

	BeginDrawing();
	ClearBackground(BLANK);

	render_background(ui);
	render_logo(ui, logo);
	render_corners(ui);

	render_question(ui, qst, font);
	render_input(ui, qst, input, font);

	EndDrawing();
}
