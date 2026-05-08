#include "time.h"

float	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	float time = ts.tv_sec;
	time += ts.tv_nsec / 1000000000.0f;

	return (time);
}
