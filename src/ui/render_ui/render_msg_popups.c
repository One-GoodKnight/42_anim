#include "ui/render_ui/colors.h"
#include "ui/ui.h"
#include "ui/msg_popup.h"
#include "raylib.h"
#include <stdio.h>

static int	min_width(t_msg_popup popup, Font font)
{
	char name_and_time[512];
	if (popup.winner)
		snprintf(name_and_time, sizeof(name_and_time), "%s   %.2f", popup.name, popup.win_time);
	else
		snprintf(name_and_time, sizeof(name_and_time), "%s", popup.name);

	int	header_width = MeasureTextEx(font, (char *)name_and_time, (float)font.baseSize, FONT_SPACING).x;
	int	msg_width = MeasureTextEx(font, (char *)popup.msg, (float)font.baseSize, FONT_SPACING).x;

	if (header_width >= msg_width)
		return (header_width);
	return (msg_width);
}

static void	render_time(t_msg_popup popup, Font font, int popup_width)
{
	char	time_text[256];
	snprintf(time_text, sizeof(time_text), "%.2f", popup.win_time);

	int time_width = MeasureTextEx(font, (char *)time_text, (float)font.baseSize, FONT_SPACING).x;

	int x = popup.x + popup_width - time_width;
	int y = popup.y;

	DrawTextEx(font, time_text, (Vector2){x, y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
}

static void	render_popup(t_msg_popup popup, Font font)
{
	int	popup_width = min_width(popup, font);

	DrawTextEx(font, popup.name, (Vector2){popup.x, popup.y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);

	DrawTextEx(font, popup.msg, (Vector2){popup.x, popup.y + 25}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);

	if (popup.winner)
		render_time(popup, font, popup_width);
}

void	render_msg_popups(t_ui *ui, Font font)
{
	int i = 0;
	while (i < ui->messages_popups.size)
	{
		t_msg_popup *msg_popup = vec_get(&ui->messages_popups, i++);

		if (!msg_popup->dead)
			render_popup(*msg_popup, font);
	}
}
