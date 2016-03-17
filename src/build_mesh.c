/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:48:11 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 16:53:20 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	setup_mesh_origin(t_mesh *mesh)
{
	size_t		i;
	GLfloat		max[3];
	GLfloat		min[3];

	i = 0;
	max[0] = -1000000;
	max[1] = -1000000;
	max[2] = -1000000;
	min[0] = 1000000;
	min[1] = 1000000;
	min[2] = 1000000;
	while (i < mesh->obj_vertex.v.size)
	{
		max[0] = fmaxf(max[0], mesh->obj_vertex.v.vertices[i]);
		max[1] = fmaxf(max[1], mesh->obj_vertex.v.vertices[i + 1]);
		max[2] = fmaxf(max[2], mesh->obj_vertex.v.vertices[i + 2]);
		min[0] = fminf(min[0], mesh->obj_vertex.v.vertices[i]);
		min[1] = fminf(min[1], mesh->obj_vertex.v.vertices[i + 1]);
		min[2] = fminf(min[2], mesh->obj_vertex.v.vertices[i + 2]);
		i += 3;
	}
	X(mesh->origin) = (min[0] + max[0]) / 2.0f;
	Y(mesh->origin) = (min[1] + max[1]) / 2.0f;
	Z(mesh->origin) = (min[2] + max[2]) / 2.0f;
}

GLuint		new_vao(void)
{
	GLuint	vaoid;

	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	return (vaoid);
}

void		build_mesh(t_mesh *mesh)
{
	t_obj			*obj;
	t_mat4x4		rotation;
	t_mat4x4		*translation;

	obj = mesh->objs;
	setup_mesh_origin(mesh);
	while (obj != NULL)
	{
		build_obj(obj, mesh);
		obj->vaoid = new_vao();
		obj->shader_program = mesh->shader_program;
		glBindVertexArray(mesh->shader_program);
		setup_obj(obj);
		setup_texture(obj);
		setup_color(obj);
		obj = obj->next;
	}
	init_mat4x4(&rotation);
	set_uniform_mat4x4(mesh->shader_program, "Rotation", &rotation);
	translation = mat_translation(-mesh->origin.data[0], -mesh->origin.data[1],
									-mesh->origin.data[2]);
	set_uniform_mat4x4(mesh->shader_program, "Translation", translation);
	init_mat4x4(translation);
	set_uniform_mat4x4(mesh->shader_program, "PostTranslation", translation);
	free(translation);
}
