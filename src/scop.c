#include <scop.h>

GLuint	new_vao()
{
	GLuint vertexArrayId;

	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	return (vertexArrayId);
}

void	create_object(t_obj *obj)
{
	printf("computing vertex buffer\n");

	obj->vertexBuffer = new_buffer(
		GL_ARRAY_BUFFER,
		obj->vertex_data.v.size,
		obj->vertex_data.v.vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	printf("Done.\n");
	printf("computing normal buffer\n");
	obj->normalBuffer = new_buffer(
		GL_ARRAY_BUFFER,
		obj->vertex_data.vn.size,
		obj->vertex_data.vn.vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	printf("Done.\n");
	obj->shaderProgram = loadShaders();
}

void	scop(t_obj *obj, t_sdl *sdl_var)
{
	init_glew();
	init_gl();

	printf("init vertexArrayId\n");
	GLuint vertexArrayId = new_vao();

	create_object(obj);

	main_loop(sdl_var, obj->shaderProgram, obj);

	printf("Cleaning\n");
	glDeleteVertexArrays(1, &(vertexArrayId));
	printf("Done\n");
}
