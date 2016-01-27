#include <scop.h>

void 		main_loop(t_sdl	*sdl_var)
{
	SDL_Event		windowEvent;
  	t_bool        quit = FALSE;

	// glUseProgram(shaderProgram);

	while (quit == FALSE)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT ||
				(windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE))
				quit = TRUE;
        }

		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
