/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:48:11 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/23 16:09:34 by dcojan           ###   ########.fr       */
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
}

void	set_uniform_mat4x4(GLuint prog, const char *name, t_mat4x4 *mat)
{
	GLuint			rot_unif_id;

	rot_unif_id = glGetUniformLocation(prog, name);
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((mat->data)[0][0]));
}

void	set_attrib_array(GLuint num, GLuint size)
{
	glEnableVertexAttribArray(num);
	glVertexAttribPointer(num, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void		compute_uv_coordinates(t_bmp_tex *tex)
{
	float		*uv;
	uint32_t	i;
	uint32_t	x;
	uint32_t	y;

	uv = (float *)malloc(sizeof(float) * ((tex->width * tex->height) * 2));
	i = 0;
	x = 0;
	y = 0;
	while (i < ((tex->width * tex->height) * 2))
	{
		uv[i] = x / tex->width;
		uv[i + 1] = y / tex->height;
		i += 2;
		x++;
		if (x == tex->width)
		{
			x = 0;
			y++;
		}
	}
	tex->uv = uv;
}

void	setup_mesh(t_mesh *mesh)
{
	t_mat4x4		*rotation;
	t_mat4x4		*translation;
	GLuint			texture_id;
	t_bmp_tex		*tex;

	mesh->vertex_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.v.size,
								mesh->vertex_data.v.vertices, GL_STATIC_DRAW);
	set_attrib_array(0, 3);
	mesh->normal_buffer = new_buffer(GL_ARRAY_BUFFER, mesh->vertex_data.vn.size,
								mesh->vertex_data.vn.vertices, GL_STATIC_DRAW);
	set_attrib_array(2, 3);
	mesh->shader_program = load_shaders();
	glUseProgram(mesh->shader_program);
	glBindVertexArray(mesh->shader_program);
	rotation = new_mat4x4();
	set_uniform_mat4x4(mesh->shader_program, "Rotation", rotation);
	setup_mesh_origin(mesh);
	translation = mat_translation(-mesh->origin.data[0], -mesh->origin.data[1],
									-mesh->origin.data[2]);
	set_uniform_mat4x4(mesh->shader_program, "Translation", translation);
	// if ((tex = load_bmp("textures/default_tex.bmp")) != NULL)
	if ((tex = load_bmp("textures/default_tex.bmp")) != NULL)
	{
		texture_id = new_texture_buffer(tex->width, tex->height, tex->data);
		compute_uv_coordinates(tex);
		new_buffer(GL_ARRAY_BUFFER, ((tex->width * tex->height) * 2),
					tex->uv, GL_STATIC_DRAW);
		set_attrib_array(1, 2);
	}
}
