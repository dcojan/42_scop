/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:42:41 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_loader.h"

FILE		*open_file(const char *path)
{
	FILE	*stream;

	printf("path = %s\n", path);
	stream = fopen(path, "r");
	if (stream == NULL)
	{
		perror("");
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

t_mesh		*load_dot_obj_file(char *path)
{
	FILE		*stream;
	t_mesh		*mesh;
	int			ret;

	printf("Opening file\n");
	if ((stream = open_file(path)) == NULL)
		return (NULL);
	mesh = new_mesh();
	printf("Loading object from file\n");
	while (1)
	{
		ret = parse_label(mesh, stream);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (NULL);
	}
	// printf("%zu vertices :\n", mesh->vertex_data.v.size);
	// print_vertice_array(mesh->vertex_data.v.vertices, mesh->vertex_data.v.size);
	// print_element_array(mesh->elements.f.element, mesh->elements.f.size);
	if (mesh->elements.f.size > 0)
		unpack_elements(mesh);
	compute_normals(mesh);
	// printf("%zu normals :\n", mesh->vertex_data.vn.size);
	// print_vertice_array(mesh->vertex_data.vn.vertices, mesh->vertex_data.vn.size);
	printf("Done.\n");
	return (mesh);
}
