/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:43 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 10:37:46 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		compute_normals(t_mesh *mesh)
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

static void	unpack_elements(t_vertex *vertex_data, t_element *elements)
{
	GLfloat		*new;
	size_t		size;
	int			vindex;
	size_t		i;
	GLushort	tmp;

	printf("Unpacking elements\n");
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
		// printf("tmp =  %u\n", tmp);
		// printf("vertex_data->vertices[tmp] =  %f\n", vertex_data->vertices[tmp]);
		// printf("A\n");
		new[vindex] = vertex_data->vertices[tmp];
		// printf("B\n");
		new[vindex + 1] = vertex_data->vertices[tmp + 1];
		// printf("C\n");
		new[vindex + 2] = vertex_data->vertices[tmp + 2];
		vindex += 3;
		i++;
	}
	free(vertex_data->vertices);
	vertex_data->vertices = new;
	vertex_data->size = size;
	printf("DONE\n");

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
	mesh->vertex_data.vt.vertices = NULL;
	mesh->vertex_data.vt.size = 0;
	mesh->elements.f.element = NULL;
	mesh->elements.f.size = 0;
	mesh->mtl_lib.path = NULL;
	mesh->mtl_lib.material = NULL;
	return (mesh);
}

void		build_mesh(t_mesh *mesh)
{
	if (mesh->elements.f.size > 0)
	{
		printf("unpacking v\n");
		unpack_elements(&(mesh->vertex_data.v), &(mesh->elements.f));
	}
	if (mesh->elements.vn.size > 0)
	{
		printf("unpacking vn -> size = %zu\n",mesh->elements.vn.size);
		unpack_elements(&(mesh->vertex_data.vn), &(mesh->elements.vn));
	}
	else
		compute_normals(mesh);
	if (mesh->elements.vt.size > 0)
	{
		printf("unpacking vt\n");
		unpack_elements(&(mesh->vertex_data.vt), &(mesh->elements.vt));
	}
}
