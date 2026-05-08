#include "ui/render_ui/colors.h"
#include "ui/ui.h"
#include "ui/msg_popup.h"
#include "raylib.h"
#include <stdio.h>

static void	render_time(t_msg_popup popup, Font font, Color color)
{
	char	time_text[256];
	snprintf(time_text, sizeof(time_text), "%.2f", popup.win_time);

	int time_width = MeasureTextEx(font, (char *)time_text, (float)font.baseSize, FONT_SPACING).x;

	int x = popup.x + popup.width - time_width;
	int y = popup.y;

	DrawTextEx(font, time_text, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, color);
}

static void	render_background(t_msg_popup popup, Color color)
{
	int	offset = POPUP_BORDER_OFFSET;
	DrawRectangle(popup.x - offset, popup.y - offset, popup.width + offset * 2, popup.height + offset * 2, color);
}

static void	render_borders(t_msg_popup popup, Color color)
{
	int width = popup.width;
	int height = popup.height;
	int	offset = POPUP_BORDER_OFFSET;
	int thickness = POPUP_BORDER_THICKNESS;

	DrawRectangle(popup.x - offset + thickness, popup.y - offset, width + offset * 2 - thickness, thickness, color);

	DrawRectangle(popup.x + width + offset, popup.y - offset, thickness, height + offset * 2, color);

	DrawRectangle(popup.x - offset, popup.y + height + offset, width + offset * 2 + thickness, thickness, color);

	DrawRectangle(popup.x - offset, popup.y - offset, thickness, height + offset * 2, color);
}

static Color compute_fade(t_msg_popup popup, Color color)
{
	float max_ttl = popup.winner ? WINNER_TTL : STD_TTL;
	float t = popup.ttl / max_ttl;
	// keep fade at 255 or open a parallel dimension and see what's behind the window
	Color fade_color = (Color){color.r * t, color.g * t, color.b * t, 255};

	return (fade_color);
}

static void	render_crown(t_msg_popup popup, Texture2D crown)
{
	int	x = popup.x + popup.width - 10;
	int	y = popup.y - 28;

	DrawTextureEx(crown, (Vector2){x, (int)y}, 0.0f, 1.0f, YELLOW);
}

static void	render_popup(t_msg_popup popup, Font font, Texture2D crown)
{
	Color color = compute_fade(popup, BORDER_COLOR);

	// render crown before background for 3d effect
	if (popup.winner)
		render_crown(popup, crown);

	render_background(popup, compute_fade(popup, BLACK));
	render_borders(popup, color);

	if (popup.winner)
		render_time(popup, font, color);

	DrawTextEx(font, popup.name, (Vector2){popup.x, (int)popup.y}, (float)font.baseSize, FONT_SPACING, color);

	int font_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;
	DrawTextEx(font, popup.msg, (Vector2){popup.x, (int)popup.y + font_height + SEPARATION_HEADER_MSG + 3}, (float)font.baseSize, FONT_SPACING, color);
}

void	render_msg_popups(t_ui *ui, Font font)
{
	t_msg_popup *winner_popup = NULL;
	int i = 0;
	while (i < ui->messages_popups.size)
	{
		t_msg_popup *msg_popup = vec_get(&ui->messages_popups, i++);

		if (!msg_popup->dead)
			render_popup(*msg_popup, font, ui->crown);

		if (msg_popup->winner == true)
			winner_popup = msg_popup;
	}

	if (winner_popup && !winner_popup->dead)
		render_popup(*winner_popup, font, ui->crown);
}
