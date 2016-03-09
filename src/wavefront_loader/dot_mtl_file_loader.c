/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:36:16 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 11:57:28 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

void		load_mtl_obj_file(t_mesh *mesh)
{
	FILE		*stream;
	// int			ret;

	printf("Loading %s\n", mesh->mtl_lib.path);
	if ((stream = open_file(mesh->mtl_lib.path)) == NULL)
	{
		return ;
	}
	fclose(stream);
	return ;
}
