#include "ui/msg_popup.h"
#include "ui/ui.h"
#include "ui/update_ui/update_ui.h"
#include "vector.h"
#include "vector2.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	compute_popup_width(t_msg_popup popup, Font font)
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

static int	compute_popup_height(Font font)
{
	int font_height = MeasureTextEx(font, "|", (float)font.baseSize, FONT_SPACING).y;
	int	popup_height = font_height * 2 + SEPARATION_HEADER_MSG;

	return(popup_height);
}

static int	rand_x(t_ui *ui, int popup_width)
{
	float min_dist_edge = ui->width * (MIN_DIST_EDGE / 100.0f);

	int range = ui->width - popup_width - min_dist_edge * 2;
	if (range <= 0)
		return (0);
	return (rand() % range + min_dist_edge);
}

static int	rand_y(t_ui *ui, int popup_height)
{
	float min_dist_edge = ui->height * (MIN_DIST_EDGE / 100.0f);

	int range = ui->height - popup_height - min_dist_edge * 2;
	if (range <= 0)
		return (0);
	return (rand() % range + min_dist_edge);
}

static t_vector2	gen_random_pos(t_ui *ui, int popup_width, int popup_height)
{
	int	cent_x = ui->width / 2;
	int cent_y = ui->height / 2;

	// no popland zone
	t_vector2 top_left = (t_vector2){cent_x - MIN_DIST_CENTER_X, cent_y - MIN_DIST_CENTER_Y};
	t_vector2 top_right= (t_vector2){cent_x + MIN_DIST_CENTER_X, cent_y - MIN_DIST_CENTER_Y};
	t_vector2 bot_right = (t_vector2){cent_x + MIN_DIST_CENTER_X, cent_y + MIN_DIST_CENTER_Y};

	int	i = 0;
	while (i++ < 30)
	{
		int x = rand_x(ui, popup_width);
		int y = rand_y(ui, popup_height);

		if (x >= top_left.x && x <= top_right.x && y >= top_right.y && y <= bot_right.y)
			continue ;

		int x2 = x + popup_width;
		int y2 = y + popup_height;

		if (x2 >= top_left.x && x2 <= top_right.x && y2 >= top_right.y && y2 <= bot_right.y)
			continue ;

		return ((t_vector2){x, y});
	}
	
	return ((t_vector2){0, 0});
}

void	add_msg_popup(t_ui *ui, char *name, char *msg, bool winner, float win_time)
{
	t_msg_popup	popup;

	strncpy((char *)&popup.name, name, sizeof(popup.name));
	strncpy((char *)&popup.msg, msg, sizeof(popup.msg));
	
	popup.winner = winner;
	popup.win_time = win_time;

	popup.width = compute_popup_width(popup, ui->fonts.font_popups);
	popup.height = compute_popup_height(ui->fonts.font_popups);

	t_vector2 rand_pos = gen_random_pos(ui, popup.width, popup.height);
	popup.x = rand_pos.x;
	popup.y = rand_pos.y;

	popup.ttl = winner ? WINNER_TTL : STD_TTL;
	popup.dead = false;

	vec_push(&ui->messages_popups, &popup);
}

static void	update_msg_popups_ttl(t_ui *ui)
{
	int i = 0;
	while (i < ui->messages_popups.size)
	{
		t_msg_popup *msg_popup = vec_get(&ui->messages_popups, i++);

		if (msg_popup->dead)
			continue ;

		msg_popup->ttl -= ui->dt;
		if (msg_popup->ttl <= 0)
			msg_popup->dead = true;
	}
}

static void	update_msg_popups_offset(t_ui *ui)
{
	int i = 0;
	while (i < ui->messages_popups.size)
	{
		t_msg_popup *msg_popup = vec_get(&ui->messages_popups, i++);

		if (msg_popup->dead)
			continue ;

		msg_popup->y -= ui->dt * POPUP_SPEED;
	}
}

void	update_msg_popups(t_ui *ui)
{
	update_msg_popups_ttl(ui);
	update_msg_popups_offset(ui);
}
