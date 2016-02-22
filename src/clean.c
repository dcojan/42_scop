/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:38 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 10:48:07 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	clean_sdl(t_sdl *sdl_var)
{
	SDL_GL_DeleteContext(sdl_var->context);
	SDL_Quit();
}

void	clean_mesh(t_mesh *mesh)
{
	glDeleteProgram(mesh->shader_program);
	glDeleteBuffers(1, &(mesh->vertex_buffer));
	glDeleteBuffers(1, &(mesh->normal_buffer));
	if (mesh->folder != NULL)
		free(mesh->folder);
	if (mesh->vertex_data.v.vertices != NULL)
		free(mesh->vertex_data.v.vertices);
	if (mesh->vertex_data.vn.vertices != NULL)
		free(mesh->vertex_data.vn.vertices);
	if (mesh->elements.f.element != NULL)
		free(mesh->elements.f.element);
	if (mesh->mtl_lib.path != NULL)
		free(mesh->mtl_lib.path);
	if (mesh->mtl_lib.material != NULL)
		free(mesh->mtl_lib.material);
	free(mesh);
}
