/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:36:16 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/17 18:17:28 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

void		load_mtl_obj_file(t_mesh *mesh)
{
	FILE		*stream;
	// int			ret;

	printf("Loading %s\n", mesh->mtl_lib.path);
	if ((stream = open_file(mesh->mtl_lib.path)) == NULL)
		return ;

}
