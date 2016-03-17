/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 10:14:58 by nhiboux           #+#    #+#             */
/*   Updated: 2016/03/16 15:18:17 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

t_obj		*new_obj(void)
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->name = NULL;
	obj->vertex_data.v.vertices = NULL;
	obj->vertex_data.v.size = 0;
	obj->vertex_data.vn.vertices = NULL;
	obj->vertex_data.vn.size = 0;
	obj->vertex_data.vt.vertices = NULL;
	obj->vertex_data.vt.size = 0;
	obj->elements.f.element = NULL;
	obj->elements.f.size = 0;
	obj->elements.f.max_size = 0;
	obj->elements.vt.element = NULL;
	obj->elements.vt.size = 0;
	obj->elements.vt.max_size = 0;
	obj->elements.vn.element = NULL;
	obj->elements.vn.size = 0;
	obj->elements.vn.max_size = 0;
	obj->usemtl = NULL;
	obj->next = NULL;
	return (obj);
}

t_mesh		*new_mesh(void)
{
	t_mesh	*mesh;

	mesh = (t_mesh*)malloc(sizeof(t_mesh));
	mesh->obj_vertex.v.vertices = NULL;
	mesh->obj_vertex.v.size = 0;
	mesh->obj_vertex.v.max_size = 0;
	mesh->obj_vertex.vn.vertices = NULL;
	mesh->obj_vertex.vn.size = 0;
	mesh->obj_vertex.vn.max_size = 0;
	mesh->obj_vertex.vt.vertices = NULL;
	mesh->obj_vertex.vt.size = 0;
	mesh->obj_vertex.vt.max_size = 0;
	mesh->folder = NULL;
	mesh->mtllib = NULL;
	mesh->objs = new_obj();
	return (mesh);
}

void		add_vec3(t_vec3 *vec, t_vertex *v)
{
	GLfloat		*new;

	if (v->size == v->max_size)
	{
		new = (GLfloat *)malloc(sizeof(GLfloat) * (3 * 10000 + v->max_size));
		v->max_size += 3 * 10000;
		memcpy(new, v->vertices, sizeof(GLfloat) * v->size);
		if (v->vertices != NULL)
			free(v->vertices);
		v->vertices = new;
	}
	v->vertices[v->size] = vec->data[0];
	v->vertices[v->size + 1] = vec->data[1];
	v->vertices[v->size + 2] = vec->data[2];
	v->size += 3;
}

void		add_vec2(t_vec3 *vec, t_vertex *v)
{
	GLfloat		*new;

	if (v->size == v->max_size)
	{
		new = (GLfloat *)malloc(sizeof(GLfloat) * (2 * 10000 + v->max_size));
		v->max_size += 2 * 10000;
		memcpy(new, v->vertices, sizeof(GLfloat) * v->size);
		if (v->vertices != NULL)
			free(v->vertices);
		v->vertices = new;
	}
	v->vertices[v->size] = vec->data[0];
	v->vertices[v->size + 1] = vec->data[1];
	v->size += 2;
}

void		add_element(GLushort *el, t_element *v, int nb)
{
	size_t		size;
	GLushort	*n;

	size = (3 * (nb - 2));
	if (v->size + size > v->max_size)
	{
		n = (GLushort *)malloc(sizeof(GLushort) * (size * 10000 + v->max_size));
		v->max_size += size * 10000;
		memcpy(n, v->element, sizeof(GLushort) * v->size);
		if (v->element != NULL)
			free(v->element);
		v->element = n;
	}
	v->element[v->size] = el[0] - 1;
	v->element[v->size + 1] = el[1] - 1;
	v->element[v->size + 2] = el[2] - 1;
	if (nb == 4)
	{
		v->element[v->size + 3] = el[2] - 1;
		v->element[v->size + 4] = el[3] - 1;
		v->element[v->size + 5] = el[0] - 1;
	}
	v->size += size;
}
