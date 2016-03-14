/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:47 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/10 17:40:43 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	new_vao(void)
{
	GLuint	vaoid;

	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	return (vaoid);
}

void	scop(t_mesh *mesh, t_sdl *sdl_var)
{
	t_obj	*obj;

	init_glew();
	init_gl();
	mesh->shader_program = load_shaders();
	glUseProgram(mesh->shader_program);
	obj = mesh->objs;
	while (obj != NULL)
	{
		build_obj(obj, mesh);
		obj->vaoid = new_vao();
		obj->shader_program = mesh->shader_program;
		// printf("%s : vao nb %d\n", obj->name, obj->vaoid);
		glBindVertexArray(mesh->shader_program);
		setup_mesh(mesh->shader_program, obj);
		setup_texture(obj);
		setup_color(obj);
		obj = obj->next;
	}
	main_loop(sdl_var, mesh);
}
