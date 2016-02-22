/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 10:18:16 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_loader.h"

static FILE	*open_file(const char *path)
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

int			consume_end_of_line(FILE *stream)
{
	char	state;
	int		ret;

	while ((ret = fread(&state, 1, 1, stream)) != 0 && state != '\n')
		;
	return (ret);
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

t_mesh		*load_dot_obj_file(char *path)
{
	FILE		*stream;
	t_mesh		*mesh;
	int			ret;

	printf("Loading %s\n", path);
	if ((stream = open_file(path)) == NULL)
		return (NULL);
	mesh = new_mesh();
	mesh->folder = make_folder_path(path);
	printf("Loading object from file\n");
	while (1)
	{
		ret = parse_label(mesh, stream);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (NULL);
	}
	if (mesh->elements.f.size > 0)
		unpack_elements(mesh);
	compute_normals(mesh);
	printf("Done.\n");
	return (mesh);
}
