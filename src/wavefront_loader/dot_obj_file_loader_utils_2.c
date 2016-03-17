/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:03:20 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:06:26 by dcojan           ###   ########.fr       */
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

char		*make_folder_path(char *file)
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

t_material	*new_material(void)
{
	t_material	*mat;

	mat = (t_material*)malloc(sizeof(t_material));
	mat->name = NULL;
	mat->next = NULL;
	mat->map_kd = NULL;
	mat->map_bump = NULL;
	mat->map_ks = NULL;
	return (mat);
}
