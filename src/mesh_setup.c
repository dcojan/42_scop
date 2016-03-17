/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:48:11 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:08:23 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	setup_mesh_origin(t_obj *mesh)
{
	size_t		i;
	GLfloat		max[3];
	GLfloat		min[3];

	i = 0;
	max[0] = -10000;
	max[1] = -10000;
	max[2] = -10000;
	min[0] = 10000;
	min[1] = 10000;
	min[2] = 10000;
	while (i < mesh->vertex_data.v.size)
	{
		max[0] = fmaxf(max[0], mesh->vertex_data.v.vertices[i]);
		max[1] = fmaxf(max[1], mesh->vertex_data.v.vertices[i + 1]);
		max[2] = fmaxf(max[2], mesh->vertex_data.v.vertices[i + 2]);
		min[0] = fminf(min[0], mesh->vertex_data.v.vertices[i]);
		min[1] = fminf(min[1], mesh->vertex_data.v.vertices[i + 1]);
		min[2] = fminf(min[2], mesh->vertex_data.v.vertices[i + 2]);
		i += 3;
	}
	X(mesh->origin) = (min[0] + max[0]) / 2.0f;
	Y(mesh->origin) = (min[1] + max[1]) / 2.0f;
	Z(mesh->origin) = (min[2] + max[2]) / 2.0f;
}

void		setup_color(t_obj *mesh)
{
	float		grey;
	size_t		i;
	GLfloat		*color;

	color = (GLfloat*)malloc(sizeof(GLfloat) * (mesh->vertex_data.v.size));
	grey = 0.4;
	i = 0;
	while (i < (mesh->vertex_data.v.size))
	{
		if (i % 9 == 0)
		{
			grey += 0.1;
			if (grey >= 1.0)
				grey = 0.4;
		}
		color[i] = grey;
		color[i + 1] = grey;
		color[i + 2] = grey;
		i += 3;
	}
	mesh->vertex_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.v.size,
								color, GL_STATIC_DRAW);
	free(color);
	set_attrib_array(4, 3);
}

void		setup_mesh(GLuint shader_program, t_obj *mesh)
{
	t_mat4x4		rotation;
	t_mat4x4		*translation;

	glBindVertexArray(mesh->vaoid);
	mesh->vertex_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.v.size,
								mesh->vertex_data.v.vertices, GL_STATIC_DRAW);
	set_attrib_array(0, 3);
	mesh->normal_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.vn.size,
								mesh->vertex_data.vn.vertices, GL_STATIC_DRAW);
	set_attrib_array(2, 3);
	init_mat4x4(&rotation);
	set_uniform_mat4x4(shader_program, "Rotation", &rotation);
	setup_mesh_origin(mesh);
	translation = mat_translation(-mesh->origin.data[0], -mesh->origin.data[1],
									-mesh->origin.data[2]);
	set_uniform_mat4x4(shader_program, "Translation", translation);
	init_mat4x4(translation);
	set_uniform_mat4x4(shader_program, "PostTranslation", translation);
	free(translation);
}
