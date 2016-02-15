/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:48:11 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:48:25 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	setup_mesh(t_mesh *mesh)
{
	printf("computing vertex buffer\n");
	mesh->vertex_buffer = new_buffer(
		GL_ARRAY_BUFFER,
		mesh->vertex_data.v.size,
		mesh->vertex_data.v.vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	printf("Done.\n");
	printf("computing normal buffer\n");
	mesh->normal_buffer = new_buffer(
		GL_ARRAY_BUFFER,
		mesh->vertex_data.vn.size,
		mesh->vertex_data.vn.vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	printf("Done.\n");
	mesh->shader_program = load_shaders();
}
