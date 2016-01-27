#include <scop.h>


void	scop()
{
	t_sdl	sdl_var;
	GLuint	shaderProgram;

	init_sdl(&sdl_var);
	init_glew();
	init_gl();

	GLuint vertexArrayId;
	init_vao(&vertexArrayId);

	shaderProgram = loadShaders();


	main_loop(&sdl_var);


	glDeleteProgram(shaderProgram); // del shader program
	glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
}


int		main(int ac, char **av)
{
	(void) ac;
	(void) av;
	scop();
	return (0);
}
