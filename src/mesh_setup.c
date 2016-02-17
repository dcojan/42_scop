/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:48:11 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/17 14:35:56 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	setup_mesh_origin(t_mesh *mesh)
{
	size_t		i;

	i = 0;
	X(mesh->origin) = 0;
	Y(mesh->origin) = 0;
	Z(mesh->origin) = 0;
	while (i < mesh->vertex_data.v.size)
	{
		X(mesh->origin) += mesh->vertex_data.v.vertices[i];
		Y(mesh->origin) += mesh->vertex_data.v.vertices[i + 1];
		Z(mesh->origin) += mesh->vertex_data.v.vertices[i + 2];
		i += 3;
	}
	X(mesh->origin) /= (mesh->vertex_data.v.size / 3.0);
	Y(mesh->origin) /= (mesh->vertex_data.v.size / 3.0);
	Z(mesh->origin) /= (mesh->vertex_data.v.size / 3.0);
	printf("origin at %f %f %f\n", X(mesh->origin), Y(mesh->origin), Z(mesh->origin));
	// i = 0;
	// while (i < mesh->vertex_data.v.size)
	// {
	// 	mesh->vertex_data.v.vertices[i] -= X(mesh->origin);
	// 	mesh->vertex_data.v.vertices[i + 1] -= Y(mesh->origin);
	// 	mesh->vertex_data.v.vertices[i + 2] -= Z(mesh->origin);
	// 	i += 3;
	// }
}

void	setup_mesh(t_mesh *mesh)
{
	t_mat4x4		*rotation;
	t_mat4x4		*position;
	GLuint			rot_unif_id;

	printf("computing vertex buffer\n");
	mesh->vertex_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.v.size,
		mesh->vertex_data.v.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	printf("Done.\n");
	printf("computing normal buffer\n");
	mesh->normal_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.vn.size,
		mesh->vertex_data.vn.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	printf("Done.\n");
	mesh->shader_program = load_shaders();
	glUseProgram(mesh->shader_program);
	glBindVertexArray(mesh->shader_program);
	rotation = new_mat4x4();
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation->data)[0][0]));
	setup_mesh_origin(mesh);
	position = new_mat4x4();
	position->data[0][0] -= mesh->origin.data[0];
	position->data[1][1] -= mesh->origin.data[1];
	position->data[2][2] -= mesh->origin.data[2];
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Position");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &(position->data[0][0]));
}
