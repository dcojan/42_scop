#include <scop.h>

void	scop(t_obj *obj)
{
	t_sdl	sdl_var;
	GLuint	shaderProgram;

	init_sdl(&sdl_var);
	init_glew();
	init_gl();

	GLuint vertexArrayId;
	init_vao(&vertexArrayId);

	GLuint	vertexBuffer = init_vertex_buffer(obj);
	// init_element_array_buffer(obj);

	shaderProgram = loadShaders();
	// init_camera();


	main_loop(&sdl_var, shaderProgram, obj);

	glDeleteProgram(shaderProgram); // del shader program
	glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
	glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
}


int		main(int ac, char **av)
{
	t_obj *obj = NULL;

	if (ac == 2)
	{
		obj = load_obj(av[1]);
		if (obj != NULL)
			scop(obj);
		else
			printf("Error : unable to load object\n");
	}
	return (0);
}
