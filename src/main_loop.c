#include <scop.h>

void 		main_loop(t_sdl	*sdl_var, GLuint shaderProgram, t_obj *obj)
{
	SDL_Event		windowEvent;
  	t_bool        quit = FALSE;

	glUseProgram(shaderProgram);
	glBindVertexArray(shaderProgram);

	set_camera(4, 3, 3, shaderProgram);
	set_light(4, 4, 4, shaderProgram);

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

        glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
