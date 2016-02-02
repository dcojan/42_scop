#include <scop.h>

void	scop(t_obj *obj)
{
	t_sdl	sdl_var;
	GLuint	shaderProgram;

	printf("init sdl\n");
	init_sdl(&sdl_var);
	printf("init glew\n");
	init_glew();
	printf("init gl\n");
	init_gl();

	printf("init vertexArrayId\n");
	GLuint vertexArrayId;
	init_vao(&vertexArrayId);

	printf("computing vertex buffer\n");
	GLuint	vertexBuffer = init_vertex_buffer(obj);
	printf("Done.\n");
	printf("computing normal buffer\n");
	GLuint	normalBuffer = init_normal_buffer(obj);
	printf("Done.\n");
	(void)normalBuffer;
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
