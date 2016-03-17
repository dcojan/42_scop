/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:21:44 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:05:26 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	fill_uv(t_vec3 *normal, GLfloat *uv, GLfloat *vertices)
{
	if (pow(PX(normal), 2) > pow(PY(normal), 2) &&
		pow(PX(normal), 2) > pow(PZ(normal), 2))
	{
		uv[0] = vertices[2];
		uv[1] = vertices[1];
	}
	else if (pow(PZ(normal), 2) > pow(PY(normal), 2) &&
		pow(PZ(normal), 2) > pow(PX(normal), 2))
	{
		uv[0] = vertices[0];
		uv[1] = vertices[1];
	}
	else if (pow(PY(normal), 2) > pow(PX(normal), 2) &&
		pow(PY(normal), 2) > pow(PZ(normal), 2))
	{
		uv[0] = vertices[0];
		uv[1] = vertices[2];
	}
}

GLfloat		*compute_uv_coordinates(t_obj *mesh)
{
	GLfloat		*uv;
	uint32_t	i;
	int			j;
	t_vec3		*normal;

	uv = (float *)malloc(sizeof(float) * ((mesh->vertex_data.v.size / 3) * 2));
	i = 0;
	j = 0;
	while (i < mesh->vertex_data.v.size)
	{
		normal = (t_vec3 *)&(mesh->vertex_data.vn.vertices[i]);
		fill_uv(normal, &(uv[j]), &(mesh->vertex_data.v.vertices[i]));
		j += 2;
		i += 3;
	}
	return (uv);
}

int			load_texture(t_obj *mesh, GLuint *id)
{
	static const char	def[] = "textures/pony.bmp";
	t_bmp_tex			*bmp;
	t_tga_tex			*tga;

	tga = NULL;
	bmp = NULL;
	if (mesh->usemtl != NULL && mesh->usemtl->map_kd != NULL &&
		(tga = load_tga(mesh->usemtl->map_kd)) != NULL)
	{
		printf("loading texture path : %s\n", mesh->usemtl->map_kd);
		*id = new_texture_buffer(tga->width, tga->height, tga->data, GL_RGB);
		free(tga->data);
		free(tga);
	}
	else
	{
		printf("loading texture path : %s\n", def);
		bmp = load_bmp(def);
		*id = new_texture_buffer(bmp->width, bmp->height, bmp->data, GL_BGR);
		free(bmp->data);
		free(bmp);
	}
	if (tga == NULL && bmp == NULL)
		return (0);
	return (1);
}

void		setup_texture(t_obj *mesh)
{
	GLuint				texture_id;
	GLfloat				*uv;

	if (load_texture(mesh, &texture_id))
	{
		if (mesh->vertex_data.vt.size == 0)
		{
			uv = compute_uv_coordinates(mesh);
			mesh->texture_buffer = new_buffer(GL_ARRAY_BUFFER,
				(mesh->vertex_data.v.size / 3) * 2, uv, GL_STATIC_DRAW);
			free(uv);
		}
		else
		{
			mesh->texture_buffer = new_buffer(GL_ARRAY_BUFFER,
				mesh->vertex_data.vt.size,
				mesh->vertex_data.vt.vertices, GL_STATIC_DRAW);
		}
		set_attrib_array(1, 2);
	}
	else
		printf("failed to load texture\n");
}
