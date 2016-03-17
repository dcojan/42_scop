/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:15 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 17:26:08 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	print_notice(void)
{
	printf("\033[36m---------------KEYBOARD---------------\n"
		"Move object :\n "
		"\taxe X + : q\n"
		"\taxe X - : a\n"
		"\taxe Y + : w\n"
		"\taxe Y - : s\n"
		"\taxe Z + : e\n"
		"\taxe Z - : d\n"
		"Reset object position : x\n"
		"Toggle pause rotation : r\n"
		"Toggle color/texture : t\n"
		"Light + : y\n"
		"Light - : h\n"
		"Zoom - : u\n"
		"Zoom - : j\n"
		"--------------------------------------\n\033[0m");
}

void	scop(t_mesh *mesh, t_sdl *sdl_var)
{
	init_glew();
	init_gl();
	mesh->shader_program = load_shaders();
	glUseProgram(mesh->shader_program);
	build_mesh(mesh);
	print_notice();
	main_loop(sdl_var, mesh);
}

int		main(int ac, char **av)
{
	t_mesh		*mesh;
	t_sdl		sdl_var;

	if (ac == 2)
	{
		mesh = load_dot_obj_file(new_mesh(), av[1]);
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
