#include "ui/corner.h"
#include "ui/ui.h"
#include <time.h>
#include <math.h>

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

void	floating_corners(t_ui *ui)
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	compute_floating_offset(&ui->top_left_corner, ts);
	compute_floating_offset(&ui->top_right_corner, ts);
	compute_floating_offset(&ui->bottom_right_corner, ts);
	compute_floating_offset(&ui->bottom_left_corner, ts);
}
