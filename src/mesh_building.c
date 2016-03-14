/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:43 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/10 18:55:15 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		compute_normals(t_obj *mesh)
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

static void	unpack_elements(t_vertex *vertex_data, t_element *elements, t_vertex *mesh)
{
	GLfloat		*new;
	size_t		size;
	int			vindex;
	size_t		i;
	GLushort	tmp;

	// printf("Unpacking %zu elements from %zu vertex_data\n", elements->size, mesh->size);
	new = (GLfloat *)malloc(sizeof(GLfloat) * (elements->size * 3));
	size = elements->size * 3;
	vindex = 0;
	i = 0;
	// printf("element->size = %zu\n", elements->size);
	// printf("size = %zu\n", size);
	while (i < elements->size)
	{
		// printf("element no %zu\n", i);
		tmp = elements->element[i] * 3;
		// printf("index =  %u\n", tmp);
		// printf("vindex =  %u\n", vindex);
		// printf("vertex_data->vertices[tmp] =  %f\n", vertex_data->vertices[tmp]);
		// if (tmp >= mesh->size)
		// {
		// 	printf("vertex_data->size = %zu - tmp = %u - i = %d\n", mesh->size, tmp, elements->element[i]);
		// }
		new[vindex] = mesh->vertices[tmp];
		new[vindex + 1] = mesh->vertices[tmp + 1];
		new[vindex + 2] = mesh->vertices[tmp + 2];
		vindex += 3;
		i++;
	}
	vertex_data->vertices = new;
	vertex_data->size = size;
	// printf("DONE\n");
}

void		build_obj(t_obj *obj, t_mesh *mesh)
{
	if (obj->elements.f.size > 0)
	{
		printf("unpacking v\n");
		unpack_elements(&(obj->vertex_data.v), &(obj->elements.f), &(mesh->obj_vertex.v));
	}
	if (obj->elements.vn.size > 0)
	{
		printf("unpacking vn -> size = %zu\n",obj->elements.vn.size);
		unpack_elements(&(obj->vertex_data.vn), &(obj->elements.vn), &(mesh->obj_vertex.vn));
	}
	else
		compute_normals(obj);
	if (obj->elements.vt.size > 0)
	{
		printf("unpacking vt\n");
		unpack_elements(&(obj->vertex_data.vt), &(obj->elements.vt), &(mesh->obj_vertex.vt));
	}
}
//
// void		build_mesh(t_mesh *mesh)
// {
// 	if (mesh->elements.f.size > 0)
// 	{
// 		printf("unpacking v\n");
// 		unpack_elements(&(mesh->vertex_data.v), &(mesh->elements.f));
// 	}
// 	if (mesh->elements.vn.size > 0)
// 	{
// 		printf("unpacking vn -> size = %zu\n",mesh->elements.vn.size);
// 		unpack_elements(&(mesh->vertex_data.vn), &(mesh->elements.vn));
// 	}
// 	else
// 		compute_normals(mesh);
// 	if (mesh->elements.vt.size > 0)
// 	{
// 		printf("unpacking vt\n");
// 		unpack_elements(&(mesh->vertex_data.vt), &(mesh->elements.vt));
// 	}
// 	if (mesh->mtl_lib.path != NULL)
// 		load_mtl_obj_file(mesh);
// }
