#include "ui/ui.h"
#include "raylib.h"
#include <stddef.h>

static Font	init_font(char *path, int size)
{
	SetTraceLogLevel(LOG_ERROR);
	Font font = LoadFontEx(path, size, NULL, 255);
	SetTraceLogLevel(LOG_WARNING);
	return font;
}

int	load_assets(t_ui *ui)
{
	Font		*font = &ui->fonts.font;
	Font		*font_popups = &ui->fonts.font_popups;
	Font		*font_anim = &ui->fonts.font_anim;
	Texture2D	*logo_texture = &ui->logo;
	Image		logo_img;
	Texture2D	*crown_texture = &ui->crown;
	Image		crown_img;

	*font = init_font("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE);
	if (!font->glyphs)
		return (-1);

	*font_popups = init_font("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE_POPUPS);
	if (!font_popups->glyphs)
		return (-1);

	*font_anim = init_font("assets/Motorblock.ttf", FONT_SIZE_ANIM_TEXT);
	if (!font_anim->glyphs)
		return (-1);

	logo_img = LoadImage("assets/42_Logo.png");
	if (!logo_img.data)
		return (-1);

	ImageColorInvert(&logo_img);
	*logo_texture = LoadTextureFromImage(logo_img);
	UnloadImage(logo_img);

	if (logo_texture->id == 0)
		return (-1);

	crown_img = LoadImage("assets/crown.png");
	if (!crown_img.data)
		return (-1);

	*crown_texture = LoadTextureFromImage(crown_img);
	UnloadImage(crown_img);

	if (crown_texture->id == 0)
		return (-1);

	return (0);
}
