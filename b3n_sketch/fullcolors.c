#include "b3n.h"

#include <stdlib.h>
#include <stdio.h>

#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))

#define COL_NBR 5
#ifdef B3N_SIMULATOR
#define FPC 200
#else
#define FPC 2000
#endif

int32_t		b3n_color_mix(int32_t col1, int32_t col2, float gain)
{
	uint32_t				r;
	uint32_t				g;
	uint32_t				b;

	r = (MID(col2, 16, 24) * gain) + (MID(col1, 16, 24) * (1 - gain));
	g = (MID(col2, 8, 16) * gain) + (MID(col1, 8, 16) * (1 - gain));
	b = (MID(col2, 0, 8) * gain) + (MID(col1, 0, 8) * (1 - gain));
	return ((r << 16) + (g << 8) + b);
}

void		still_colors(s_b3n_light* lights)
{
	static const int32_t	colors[] = {0xFF0000, 0X00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF};
	static unsigned int		tick_count = 0;
	int						curr_color;
	s_b3n_light*			light;
	unsigned int			i;

	curr_color = (tick_count / 200) % 5;
	light = lights;
	while (light != NULL)
	{
		i = 0;
		while (i < light->led_nbr)
		{
			light->colors[i] = colors[curr_color];
			i++;
		}
		light = light->next;
	}
	tick_count++;
}

void		color_blend(s_b3n_light* lights)
{
	static const int32_t	colors[] = {0xB1CD02, 0x3DBF34, 0X00E0B9, 0x852466, 0xF8235F};
	static unsigned int		tick_count = 0;
	int						curr_color;
	s_b3n_light*			light;
	unsigned int			i;

	curr_color = (tick_count / FPC) % COL_NBR;
	light = lights;
	while (light != NULL)
	{
		i = 0;
		while (i < light->led_nbr)
		{
			light->colors[i] = b3n_color_mix(colors[curr_color], colors[(curr_color + 1) % COL_NBR], (tick_count % FPC) / (float)FPC);
			i++;
		}
		light = light->next;
	}
	tick_count++;
}

void		merrygoround(s_b3n_light* lights)
{
	static const int32_t	colors[] = {0xB1CD02, 0x3DBF34, 0X00E0B9, 0x852466, 0xF8235F};
	static unsigned int		tick_count = 0;
	int						curr_color;
	s_b3n_light*			light;
	unsigned int			i;

	curr_color = (tick_count / FPC) % COL_NBR;
	light = lights;
	while (light != NULL)
	{
		i = 0;
		while (i < light->led_nbr)
		{
			if (i == (tick_count / (FPC / light->led_nbr)) % light->led_nbr)
				light->colors[i] = 0xFFFFFF;
			else
				light->colors[i] = b3n_color_mix(colors[curr_color], colors[(curr_color + 1) % COL_NBR], (tick_count % FPC) / (float)FPC);
			i++;
		}
		light = light->next;
	}
	tick_count++;
}

void		b3n_update_colors(s_b3n_light* lights)
{
	merrygoround(lights);
}


