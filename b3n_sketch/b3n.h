#ifndef B3N_H
# define B3N_H

# include <stdbool.h>
# include <stdint.h>

typedef struct			t_b3n_light
{
	unsigned int			led_nbr;
	unsigned int			size;
	float				angle;
	int			        x;
	int				y;
	struct t_b3n_light*		next;
	int32_t			        color;
}						s_b3n_light;

typedef struct			t_b3n_env
{
	s_b3n_light*	        lights;
}						s_b3n_env;

s_b3n_light*			b3n_create_lights(void);

void					b3n_update_colors(s_b3n_env* env);

#endif
