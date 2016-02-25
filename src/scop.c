/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:47 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:48:05 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	new_vao(void)
{
	GLuint	vaoid;

	printf("init vertexArrayId\n");
	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	return (vaoid);
}

void	scop(t_mesh *mesh, t_sdl *sdl_var)
{
	GLuint	vaoid;

	init_glew();
	init_gl();
	vaoid = new_vao();
	mesh->shader_program = load_shaders();
	glUseProgram(mesh->shader_program);
	glBindVertexArray(mesh->shader_program);
	setup_mesh(mesh);
	main_loop(sdl_var, mesh);
	printf("Cleaning\n");
	glDeleteVertexArrays(1, &(vaoid));
	printf("Done\n");
}
