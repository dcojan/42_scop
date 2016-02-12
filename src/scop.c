/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:47 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:13:47 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

GLuint	new_vao(void)
{
	GLuint	vaoid;

	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	return (vaoid);
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
	obj->shaderProgram = load_shaders();
}

void	scop(t_obj *obj, t_sdl *sdl_var)
{
	GLuint	vaoid;

	init_glew();
	init_gl();
	printf("init vertexArrayId\n");
	vaoid = new_vao();
	create_object(obj);
	main_loop(sdl_var, obj->shaderProgram, obj);
	printf("Cleaning\n");
	glDeleteVertexArrays(1, &(vaoid));
	printf("Done\n");
}
