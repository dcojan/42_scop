/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:43 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:02:42 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	compute_normals(t_obj *mesh)
{
	t_vec3		*tmp[3];
	size_t		i;
	t_vec3		*normal;
	GLfloat		*dest;

	printf("Computing normals.\n");
	dest = (GLfloat*)malloc(sizeof(GLfloat) * mesh->vertex_data.v.size);
	mesh->vertex_data.vn.size = mesh->vertex_data.v.size;
	i = 0;
	while (i < mesh->vertex_data.v.size)
	{
		tmp[0] = (t_vec3*)&(mesh->vertex_data.v.vertices[i]);
		tmp[1] = (t_vec3*)&(mesh->vertex_data.v.vertices[i + 3]);
		tmp[2] = (t_vec3*)&(mesh->vertex_data.v.vertices[i + 6]);
		normal = (t_vec3 *)&(dest[i]);
		compute_normal(tmp[0], tmp[1], tmp[2], normal);
		memcpy(&(normal[1]), &(normal[0]), sizeof(GLfloat) * 3);
		memcpy(&(normal[2]), &(normal[0]), sizeof(GLfloat) * 3);
		i += 9;
	}
	mesh->vertex_data.vn.vertices = dest;
}

static void	unpack_elements(t_vertex *v, t_element *e, t_vertex *mesh, int nb)
{
	GLfloat		*new;
	size_t		size;
	int			vindex;
	size_t		i;
	GLushort	tmp;

	new = (GLfloat *)malloc(sizeof(GLfloat) * (e->size * nb));
	size = e->size * nb;
	vindex = 0;
	i = 0;
	while (i < e->size)
	{
		tmp = e->element[i] * nb;
		new[vindex] = mesh->vertices[tmp];
		new[vindex + 1] = mesh->vertices[tmp + 1];
		if (nb == 3)
			new[vindex + 2] = mesh->vertices[tmp + 2];
		vindex += nb;
		i++;
	}
	v->vertices = new;
	v->size = size;
}

void		build_obj(t_obj *obj, t_mesh *mesh)
{
	if (obj->elements.f.size > 0)
	{
		unpack_elements(&(obj->vertex_data.v),
		&(obj->elements.f), &(mesh->obj_vertex.v), 3);
	}
	else
	{
		obj->vertex_data.v = mesh->obj_vertex.v;
		mesh->obj_vertex.v.vertices = NULL;
		mesh->obj_vertex.v.size = 0;
	}
	if (obj->elements.vn.size > 0)
	{
		unpack_elements(&(obj->vertex_data.vn), &(obj->elements.vn),
						&(mesh->obj_vertex.vn), 3);
	}
	else
		compute_normals(obj);
	if (obj->elements.vt.size > 0)
	{
		unpack_elements(&(obj->vertex_data.vt), &(obj->elements.vt),
						&(mesh->obj_vertex.vt), 2);
	}
}
