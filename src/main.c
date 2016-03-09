/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:15 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 16:58:31 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		main(int ac, char **av)
{
	t_mesh		*mesh;
	t_obj		*obj;
	t_sdl		sdl_var;

	if (ac == 2)
	{
		mesh = load_dot_obj_file(new_mesh(), av[1]);
		if (mesh != NULL)
		{
			init_sdl(&sdl_var);
			// if (mesh->mtllib != NULL)
				// load_mtl_obj_file(&(mesh->mtllib));
			obj = mesh->objs;
			while (obj != NULL)
			{
				build_obj(obj, mesh);
				obj = obj->next;
			}
			scop(mesh, &sdl_var);
			if (mesh->folder != NULL)
				free(mesh->folder);
			clean_mesh(mesh);
			glDeleteProgram(mesh->shader_program);
			clean_sdl(&sdl_var);
		}
		else
			printf("Error : unable to load object\n");
	}
	else
		printf("Usage :\n$> ./scop file.obj\n");
	return (0);
}
