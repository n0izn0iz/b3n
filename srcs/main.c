#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "b3n.h"

void			sdl_error(const char* str)
{
	fprintf(stderr, "%s: %s\n", str, SDL_GetError());
	exit(-1);
}

void			b3n_init(s_b3n_env*	env)
{
	if (SDL_Init(0))
		sdl_error("Unable to initialize SDL: %s\n");
	atexit(SDL_Quit);
	if ((env->window = SDL_CreateWindow("b3n", 0, 0, WIN_WIDTH, WIN_HEIGHT, 0)) == NULL)
		sdl_error("Unable to create window: %s\n");
	if ((env->renderer = SDL_CreateRenderer(env->window, -1, 0)) == NULL)
		sdl_error("Unable to create renderer: %s\n");
	if ((env->texture = SDL_CreateTexture(env->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		sdl_error("Unable to create Texture: %s\n");
	env->running = true;
	env->lights = b3n_create_lights();
}

void			b3n_handle_events(s_b3n_env*	env)
{
	SDL_Event e;

	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		env->running = false;
}

void			b3n_update_window(const s_b3n_env*	env)
{
	SDL_RenderClear(env->renderer);
	SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
	SDL_RenderPresent(env->renderer);
	SDL_UpdateTexture(env->texture, NULL, env->pixels, WIN_WIDTH * sizeof(uint32_t));
}

void			b3n_cleanup(s_b3n_env*	env)
{
	b3n_destroy_lights(&(env->lights));
	SDL_DestroyTexture(env->texture);
	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->window);
}

int		main(void)
{
	s_b3n_env env;

	b3n_init(&env);
	while(env.running)
	{
		b3n_handle_events(&env);
		b3n_update_colors(&env);
		b3n_draw_lights(&env);
		b3n_update_window(&env);
	}
	b3n_cleanup(&env);
	return (0);
}
