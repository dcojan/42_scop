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

	GLuint	vertexBuffer = init_vertex_buffer();

	shaderProgram = loadShaders();
	// init_camera();


	main_loop(&sdl_var, shaderProgram);


	glDeleteProgram(shaderProgram); // del shader program
	glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
	glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
}


int		main(int ac, char **av)
{
	if (ac == 2)
		load_obj(av[1]);
	//scop();
	return (0);
}
