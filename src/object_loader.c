/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:13:41 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			consume_end_of_line(FILE *stream)
{
	char	state;
	int		ret;

	while ((ret = fread(&state, 1, 1, stream)) != 0 && state != '\n')
		;
	return (ret);
}

t_obj		*load_obj(char *path)
{
	FILE		*stream;
	t_obj		*obj;
	int			ret;

	printf("Opening file\n");
	if ((stream = open_file(path)) == NULL)
		return (NULL);
	obj = new_obj();
	printf("Loading object from file\n");
	while (1)
	{
		ret = parse_label(obj, stream);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (NULL);
	}
	// printf("%zu vertices :\n", obj->vertex_data.v.size);
	// print_vertice_array(obj->vertex_data.v.vertices, obj->vertex_data.v.size);
	// print_element_array(obj->elements.f.element, obj->elements.f.size);
	if (obj->elements.f.size > 0)
		unpack_elements(obj);
	compute_normals(obj);
	// printf("%zu normals :\n", obj->vertex_data.vn.size);
	// print_vertice_array(obj->vertex_data.vn.vertices, obj->vertex_data.vn.size);

	printf("Done.\n");
	return (obj);
}
