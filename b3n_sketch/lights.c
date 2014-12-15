#include <stdlib.h>

#include "b3n.h"

s_b3n_light*	b3n_create_lights(void)
{
	s_b3n_light*	light;
	s_b3n_light*	first;
	unsigned int	size;
	int				yoffset;

	size = 120;
	yoffset = -60;
	light = malloc(sizeof(s_b3n_light));
	first = light;
	light->led_nbr = 11;
	light->size = 80;
	light->x = 0;
	light->y = size + yoffset;
	light->next = malloc(sizeof(s_b3n_light));
	light = light->next;
	light->led_nbr = 11;
	light->size = 40;
	light->x = size;
	light->y = yoffset;
	light->next = malloc(sizeof(s_b3n_light));
	light = light->next;
	light->led_nbr = 6;
	light->size = 20;
	light->x = 0;
	light->y = -(size / 2) + yoffset;
	light->next = malloc(sizeof(s_b3n_light));
	light = light->next;
	light->led_nbr = 8;
	light->size = 40;
	light->x = -size;
	light->y = yoffset;
	light->next = NULL;
	light = first;
	while(light)
	{
		light->colors = malloc(sizeof(int32_t) * light->led_nbr);
		light = light->next;
	}
	return (first);
}

#ifdef B3N_SIMULATOR
void		b3n_destroy_lights(s_b3n_light** light)
{
	s_b3n_light* curr;
	s_b3n_light* tmp;

	curr = *light;
	while (curr != NULL)
	{
		free(curr->colors);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*light = NULL;
}

void		b3n_draw_lights(s_b3n_env* env)
{
	s_b3n_light*	light;

	light = env->lights;
	while(light != NULL)
	{
		b3n_draw_circle(light->x, light->y, light->size, 0xFFFFFF, env);
		b3n_draw_circleofcircles(light->x, light->y, light->size, light->angle, light->colors, light->led_nbr, env);
		light = light->next;
	}
}
#endif
