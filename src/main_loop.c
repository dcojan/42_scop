#include <scop.h>
// 	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
// 	 ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);

t_mat4x4	*perspective(GLfloat fovy, GLfloat ratio, GLfloat near, GLfloat far)
{
    t_mat4x4	*mat;
    GLfloat		tan_half_angle;

    if (ratio == 0 || near == far)
    {
        printf("ratio == 0 or near == far\n");
        exit(-1);
    }
    mat = new_mat4x4();
    // mat_zero(to_return);
    tan_half_angle = tan(fovy / 2.0f);
    (*mat)[0][0] = 1.0f / (ratio * tan_half_angle);
    (*mat)[1][1] = 1.0f / tan_half_angle;
    (*mat)[2][2] = -(far + near) / (far - near);
    (*mat)[2][3] = -1.0f;
    (*mat)[3][2] = -(2.0f * far * near) / (far - near);
    (*mat)[3][3] = 0.0f;
    return (mat);
}



void 		main_loop(t_sdl	*sdl_var, GLuint shaderProgram)
{
	SDL_Event		windowEvent;
  	t_bool        quit = FALSE;

	glUseProgram(shaderProgram);
	glBindVertexArray(shaderProgram);


    // t_mat4x4 *ProjectionMatrix = perspective(0.785398f, (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    // t_mat4x4 *ProjectionMatrix = perspective(0.785398f, 4.0f / 3.0f, 0.1f, 100.0f);
	t_mat4x4 *ProjectionMatrix = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	t_vec3 eye = {4,3,3};
	t_vec3 center = {0,0,0};
	t_vec3 up = {0,1,0};
	t_mat4x4 * ViewMatrix = lookAt(&eye, &center, &up);
	t_mat4x4 mvp;
	mul_mat4x4(ViewMatrix, ProjectionMatrix, &mvp);
	print_mat(ProjectionMatrix);
	print_mat(ViewMatrix);
	print_mat(&mvp);

    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(mvp)[0][0]);
	// glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(*ViewMatrix)[0][0]);
	// glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(*ProjectionMatrix)[0][0]);
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

		glDrawArrays(GL_TRIANGLES,0,36);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
