#include "ui/render_ui/colors.h"
#include "ui/ui.h"
#include "ui/msg_popup.h"
#include "raylib.h"
#include <stdio.h>

static void	render_popup(t_msg_popup popup, Font font)
{
	DrawTextEx(font, popup.msg, (Vector2){popup.x, popup.y}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);

	if (popup.winner == false)
		return ;

	char	time_text[256];
	snprintf(time_text, sizeof(time_text), "%.2f", popup.win_time);

	DrawTextEx(font, time_text, (Vector2){popup.x, popup.y + 20}, (float)font.baseSize, FONT_SPACING, FONT_COLOR);
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
