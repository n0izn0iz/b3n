#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "b3n.h"

void		b3n_put_pixel(int32_t color, unsigned int x, unsigned int y, s_b3n_env* env)
{
	if (y >= WIN_HEIGHT || x >= WIN_WIDTH)
		return ;
	env->pixels[y * WIN_WIDTH + x] = color;
}

void		b3n_draw_circle(int x, int y, unsigned int size, int32_t color, s_b3n_env* env)
{
	float		angle;

	int xbase = WIN_WIDTH / 2 - x;
	int ybase = WIN_HEIGHT / 2 - y;
	angle = 0.f;
	while (angle < 360.f)
	{
		b3n_put_pixel(color, xbase + (size * cos(RAD(angle))), ybase + (size * sin(RAD(angle))), env);
		angle += size * M_PI / 360.f;
	}
}

void		b3n_draw_circleofcircles(int x, int y, unsigned int size, float angle, int32_t color, unsigned int nbr, s_b3n_env* env)
{
	float				offset;
	unsigned int		i;

	if (nbr < 3)
		return ;
	offset = 360.f / nbr;
	i = 0;
	while (i < nbr)
	{
		b3n_draw_circle(x + (size * cos(RAD(angle + (i * offset)))), y + (size * sin(RAD(angle + (i * offset)))), (size * M_PI) / nbr, color, env);
		i++;
	}
}
