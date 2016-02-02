#include <scop.h>

void 		main_loop(t_sdl	*sdl_var, GLuint shaderProgram, t_obj *obj)
{
	SDL_Event		windowEvent;
  	t_bool        quit = FALSE;

	glUseProgram(shaderProgram);
	glBindVertexArray(shaderProgram);

	////// CAMERA
	t_mat4x4 *ProjectionMatrix = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	t_vec3 eye = {4,3,3};
	// t_vec3 eye = {1,1,3};
	t_vec3 center = {0,0,0};
	t_vec3 up = {0,1,0};
	t_mat4x4 * ViewMatrix = lookAt(&eye, &center, &up);
	t_mat4x4 mvp;
    mul_mat4x4(ViewMatrix, ProjectionMatrix, &mvp);
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(shaderProgram, "V");
	GLuint ModelMatrixID = glGetUniformLocation(shaderProgram, "M");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(mvp)[0][0]);
	t_mat4x4 ModelMatrix;
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &((*ViewMatrix)[0][0]));
    // print_mat(ProjectionMatrix);
	// print_mat(ViewMatrix);
	// print_mat(&mvp);
	//////

	////// LIGHT
	GLuint LightID = glGetUniformLocation(shaderProgram, "light_position_worldspace");
	t_vec3 lightPos = {4,4,4};
	glUniform3f(LightID, lightPos[0], lightPos[1], lightPos[2]);


	// printf("vertice count : %zu  -  face count %zu\n",  obj->vertex_data.v.size,  obj->elements.f.size);
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
		// glDrawArrays(GL_TRIANGLES,0, obj->vertex_data.v.size / 3);
        // glDrawElements(
        //     GL_TRIANGLES,      // mode
        //     obj->elements.f.size,    // count
        //     GL_UNSIGNED_SHORT,   // type
        //     (void*)0           // element array buffer offset
        // );
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
