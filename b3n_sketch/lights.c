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
	return (first);
}
