#include <scop.h>

void	clean_object(t_obj *obj)
{
	glDeleteProgram(obj->shaderProgram);
	glDeleteBuffers(1, &(obj->vertexBuffer));
	glDeleteBuffers(1, &(obj->normalBuffer));
	if (obj->vertex_data.v.vertices != NULL)
		free(obj->vertex_data.v.vertices);
	if (obj->vertex_data.vn.vertices != NULL)
		free(obj->vertex_data.vn.vertices);
	if (obj->elements.f.element != NULL)
		free(obj->elements.f.element);
	free(obj);
}

void	create_object(t_obj *obj)
{
	printf("computing vertex buffer\n");
	obj->vertexBuffer = init_vertex_buffer(obj);
	printf("Done.\n");
	printf("computing normal buffer\n");
	obj->normalBuffer = init_normal_buffer(obj);
	printf("Done.\n");
	obj->shaderProgram = loadShaders();
}

GLuint	new_vao()
{
	GLuint vertexArrayId;

	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	return (vertexArrayId);
}

void	scop(t_obj *obj)
{
	t_sdl	sdl_var;

	init_sdl(&sdl_var);
	init_glew();
	init_gl();

	printf("init vertexArrayId\n");
	GLuint vertexArrayId = new_vao();

	create_object(obj);

	main_loop(&sdl_var, obj->shaderProgram, obj);

	printf("Cleaning\n");
	glDeleteVertexArrays(1, &(vertexArrayId));
	clean_object(obj);
	clean_sdl(&sdl_var);
	printf("Done\n");
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
	else
		printf("Usage :\n$> ./scop file.obj\n");
	return (0);
}
