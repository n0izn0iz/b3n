#ifndef B3N_H
# define B3N_H

# ifdef B3N_SIMULATOR
#  include <stdbool.h>
#  include <SDL2/SDL.h>

#  define WIN_HEIGHT	400
#  define WIN_WIDTH	400

#  define RAD(x) ((x) * (M_PI / 180))
# endif

typedef struct			t_b3n_light
{
	unsigned int			led_nbr;
	unsigned int			size;
	float					angle;
	int						x;
	int						y;
	struct t_b3n_light*		next;
	int32_t					color;
}						s_b3n_light;

typedef struct			t_b3n_env
{
# ifdef B3N_SIMULATOR
	bool		running;
	SDL_Window*	window;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	int32_t		pixels[WIN_WIDTH * WIN_HEIGHT];
# endif
	s_b3n_light*	lights;
}						s_b3n_env;

s_b3n_light*			b3n_create_lights(void);

void					b3n_update_colors(s_b3n_env* env);

# ifdef B3N_SIMULATOR
void					b3n_destroy_lights(s_b3n_light** light);
void					b3n_draw_lights(s_b3n_env* env);

void					b3n_draw_circle(int x, int y, unsigned int size, int32_t color, s_b3n_env* env);
void					b3n_draw_circleofcircles(int x, int y, unsigned int size, float angle, int32_t color, unsigned int nbr, s_b3n_env* env);
# endif

#endif
