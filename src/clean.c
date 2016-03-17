/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:38 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:39:43 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	clean_sdl(t_sdl *sdl_var)
{
	printf("clean sdl\n");
	SDL_GL_DeleteContext(sdl_var->context);
	SDL_Quit();
}

void	clean_obj(t_obj *obj)
{
	glDeleteBuffers(1, &(obj->vertex_buffer));
	glDeleteBuffers(1, &(obj->normal_buffer));
	glDeleteBuffers(1, &(obj->texture_buffer));
	if (obj->name != NULL)
		free(obj->name);
	if (obj->vertex_data.v.vertices != NULL)
		free(obj->vertex_data.v.vertices);
	if (obj->vertex_data.vn.vertices != NULL)
		free(obj->vertex_data.vn.vertices);
	if (obj->vertex_data.vt.vertices != NULL)
		free(obj->vertex_data.vt.vertices);
	if (obj->elements.f.element != NULL)
		free(obj->elements.f.element);
	if (obj->elements.vn.element != NULL)
		free(obj->elements.vn.element);
	if (obj->elements.vt.element != NULL)
		free(obj->elements.vt.element);
	glDeleteVertexArrays(1, &(obj->vaoid));
	free(obj);
}

void	clean_material(t_material *mat)
{
	if (mat == NULL)
		return ;
	clean_material(mat->next);
	printf("clean material : %s\n", mat->name);
	if (mat->map_kd != NULL)
		free(mat->map_kd);
	free(mat->name);
	free(mat);
}

void	clean_mesh(t_mesh *mesh)
{
	t_obj		*obj;

	printf("clean mesh\n");
	glDeleteProgram(mesh->shader_program);
	if (mesh->folder != NULL)
		free(mesh->folder);
	if (mesh->mtllib != NULL)
		free(mesh->mtllib);
	clean_material(mesh->material);
	while (mesh->objs != NULL)
	{
		obj = mesh->objs;
		mesh->objs = mesh->objs->next;
		clean_obj(obj);
	}
	if (mesh->obj_vertex.v.vertices != NULL)
		free(mesh->obj_vertex.v.vertices);
	if (mesh->obj_vertex.vn.vertices != NULL)
		free(mesh->obj_vertex.vn.vertices);
	if (mesh->obj_vertex.vt.vertices != NULL)
		free(mesh->obj_vertex.vt.vertices);
	free(mesh);
}
