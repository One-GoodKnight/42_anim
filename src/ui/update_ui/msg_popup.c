#include "ui/msg_popup.h"
#include "ui/ui.h"
#include "vector.h"
#include <stdbool.h>
#include <string.h>

void	add_msg_popup(t_ui *ui, char *name, char *msg, bool winner, float win_time)
{
	t_msg_popup	popup;

	strncpy((char *)&popup.name, name, sizeof(popup.name));
	strncpy((char *)&popup.msg, msg, sizeof(popup.msg));
	
	popup.winner = winner;
	popup.win_time = win_time;

	popup.x = 200;
	popup.y = 200;

	popup.ttl = winner ? WINNER_TTL : STD_TTL;
	popup.dead = false;

	vec_push(&ui->messages_popups, &popup);
}

void	update_msg_popups_ttl(t_ui *ui)
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
