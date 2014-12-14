#include "b3n.h"

#define COL_NBR 5

void		b3n_update_colors(s_b3n_env* env)
{
	static const int32_t	colors[] = {0xFF0000, 0X00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF};
	static unsigned int		tick_count = 0;
	int						curr_color;
	s_b3n_light*			light;

	curr_color = (tick_count / 200) % 5;
	light = env->lights;
	while (light != NULL)
	{
		light->color = colors[curr_color];
		light = light->next;
	}
	tick_count++;
}
