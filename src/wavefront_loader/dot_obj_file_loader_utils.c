/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 10:14:58 by nhiboux           #+#    #+#             */
/*   Updated: 2016/03/09 11:57:26 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

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
