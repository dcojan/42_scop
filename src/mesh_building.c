/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:43 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 10:46:17 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		compute_normals(t_mesh *mesh)
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

void		unpack_elements(t_mesh *mesh)
{
	GLfloat		*new;
	size_t		size;
	int			vindex;
	size_t		i;
	GLushort	tmp;

	printf("Unpacking elements\n");
	new = (GLfloat *)malloc(sizeof(GLfloat) * (mesh->elements.f.size * 3));
	size = mesh->elements.f.size * 3;
	vindex = 0;
	i = 0;
	while (i < mesh->elements.f.size)
	{
		tmp = mesh->elements.f.element[i] * 3;
		new[vindex] = mesh->vertex_data.v.vertices[tmp];
		new[vindex + 1] = mesh->vertex_data.v.vertices[tmp + 1];
		new[vindex + 2] = mesh->vertex_data.v.vertices[tmp + 2];
		vindex += 3;
		i++;
	}
	free(mesh->vertex_data.v.vertices);
	mesh->vertex_data.v.vertices = new;
	mesh->vertex_data.v.size = size;
}

void		add_vec3(t_vec3 *vec, t_vertex *v)
{
	GLfloat		*new;

	new = (GLfloat *)malloc(sizeof(GLfloat) * (v->size + 3));
	if (v->size > 0)
		memcpy(new, v->vertices, sizeof(GLfloat) * v->size);
	new[v->size] = vec->data[0];
	new[v->size + 1] = vec->data[1];
	new[v->size + 2] = vec->data[2];
	if (v->vertices != NULL)
		free(v->vertices);
	v->vertices = new;
	v->size += 3;
}

void		add_element(GLushort *el, t_element *v, int nb)
{
	size_t		size;
	GLushort	*new;

	size = (v->size + (3 * (nb - 2)));
	new = (GLushort *)malloc(sizeof(GLushort) * size);
	if (v->size > 0)
		memcpy(new, v->element, sizeof(GLushort) * v->size);
	new[v->size] = el[0] - 1;
	new[v->size + 1] = el[1] - 1;
	new[v->size + 2] = el[2] - 1;
	if (nb == 4)
	{
		new[v->size + 3] = el[2] - 1;
		new[v->size + 4] = el[3] - 1;
		new[v->size + 5] = el[0] - 1;
	}
	if (v->element != NULL)
		free(v->element);
	v->element = new;
	v->size = size;
}

t_mesh		*new_mesh(void)
{
	t_mesh	*mesh;

	mesh = (t_mesh*)malloc(sizeof(t_mesh));
	mesh->folder = NULL;
	mesh->vertex_data.v.vertices = NULL;
	mesh->vertex_data.v.size = 0;
	mesh->vertex_data.vn.vertices = NULL;
	mesh->vertex_data.vn.size = 0;
	mesh->elements.f.element = NULL;
	mesh->elements.f.size = 0;
	mesh->mtl_lib.path = NULL;
	mesh->mtl_lib.material = NULL;
	return (mesh);
}
