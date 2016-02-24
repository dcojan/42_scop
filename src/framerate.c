#include "scop.h"
#include <sys/time.h>
#include <unistd.h>

unsigned long		get_time()
{
	struct timeval			t;

	gettimeofday(&t, NULL);
	return (1000000 * t.tv_sec + t.tv_usec);
}

void				framerate_control(double *next_game_tick)
{
	static unsigned long		t_start = 0;
	unsigned long				now;
	double						sleep_time;

	*next_game_tick += SKIP_TICKS;
	if (t_start == 0)
		t_start = get_time();
	now = get_time();
	sleep_time = *next_game_tick - ((double)(now - t_start) / 1000.0);
	if (sleep_time >= 0)
	{
		usleep(1000 * sleep_time);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
}
