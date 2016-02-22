/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:15 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 10:08:59 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		main(int ac, char **av)
{
	t_mesh		*mesh;
	t_sdl		sdl_var;

	if (ac == 2)
	{
		mesh = load_dot_obj_file(av[1]);
		if (mesh->mtl_lib.path != NULL)
			load_mtl_obj_file(mesh);
		if (mesh != NULL)
		{
			init_sdl(&sdl_var);
			scop(mesh, &sdl_var);
			clean_mesh(mesh);
			clean_sdl(&sdl_var);
		}
		else
			printf("Error : unable to load object\n");
	}
	else
		printf("Usage :\n$> ./scop file.obj\n");
	return (0);
}
