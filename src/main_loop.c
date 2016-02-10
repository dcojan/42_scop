#include <scop.h>

void		main_loop(t_sdl *sdl_var, GLuint program, t_obj *obj)
{
	SDL_Event		window_event;
	t_bool			quit;

	quit = FALSE;
	glUseProgram(program);
	glBindVertexArray(program);
	set_camera(4, 3, 3, program);
	set_light(4, 4, 4, program);
	while (quit == FALSE)
	{
		if (SDL_PollEvent(&window_event))
		{
			if (window_event.type == SDL_QUIT ||
				(window_event.type == SDL_KEYUP &&
				window_event.key.keysym.sym == SDLK_ESCAPE))
				quit = TRUE;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
