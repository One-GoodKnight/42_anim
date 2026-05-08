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

static int	load_texture(char *path, Texture2D **texture, bool invert_color)
{
	Image		img;

	img = LoadImage(path);
	if (!img.data)
		return (-1);

	if (invert_color)
		ImageColorInvert(&img);
	**texture = LoadTextureFromImage(img);
	UnloadImage(img);

	if ((*texture)->id == 0)
		return (-1);

	return (0);
}

int	load_assets(t_ui *ui)
{
	Font		*font = &ui->fonts.font;
	Font		*font_popups = &ui->fonts.font_popups;
	Font		*font_anim = &ui->fonts.font_anim;
	Texture2D	*logo_texture = &ui->logo;
	Texture2D	*crown_texture = &ui->crown;
	Texture2D	*train_texture = &ui->train;

	*font = init_font("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE);
	if (!font->glyphs)
		return (-1);

	*font_popups = init_font("assets/JetBrainsMonoNL-Regular.ttf", FONT_SIZE_POPUPS);
	if (!font_popups->glyphs)
		return (-1);

	*font_anim = init_font("assets/Motorblock.ttf", FONT_SIZE_ANIM_TEXT);
	if (!font_anim->glyphs)
		return (-1);

	if (load_texture("assets/42_logo.png", &logo_texture, true) == -1)
		return (-1);

	if (load_texture("assets/crown.png", &crown_texture, false) == -1)
		return (-1);

	if (load_texture("assets/train.png", &train_texture, false) == -1)
		return (-1);

	return (0);
}
