/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 10:14:58 by nhiboux           #+#    #+#             */
/*   Updated: 2016/03/15 17:35:59 by nhiboux          ###   ########.fr       */
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

FILE		*open_file(const char *path)
{
	FILE	*stream;

	stream = fopen(path, "r");
	if (stream == NULL)
	{
		perror(path);
		return (NULL);
	}
	return (stream);
}

char		*make_folder_path(char* file)
{
	size_t		size;

	size = strlen(file) - 1;
	while (size)
	{
		if (file[size] == '/')
		{
			file[size + 1] = '\0';
				break ;
		}
		size--;
	}
	if (size == 0)
		return (strdup("./"));
	return (strdup(file));
}

int			consume_end_of_line(FILE *stream)
{
	char	state;
	int		ret;

	while ((ret = fread(&state, 1, 1, stream)) != 0 && state != '\n')
		;
	return (ret);
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
	GLushort	*new;

	size = (3 * (nb - 2));
	// printf("%zu/%zu\n", v->size, v->max_size);
	if (v->size + size > v->max_size)
	{
		new = (GLushort *)malloc(sizeof(GLushort) * (size * 10000 + v->max_size));
		v->max_size += size * 10000;
		memcpy(new, v->element, sizeof(GLushort) * v->size);
		if (v->element != NULL)
			free(v->element);
		v->element = new;
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

void		print_vertice_array(GLfloat *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		printf("%f %f %f\n", array[i], array[i + 1], array[i + 2]);
		i += 3;
	}
}

void		print_element_array(GLushort *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		printf("%hd ", array[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
		i++;
	}
	printf("\n");
}
