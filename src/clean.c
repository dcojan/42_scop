/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:38 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 22:41:02 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	clean_sdl(t_sdl *sdl_var)
{
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
	if (obj->usemtl != NULL)
	{
		free(obj->usemtl->name);
		free(obj->usemtl);
	}
	glDeleteVertexArrays(1, &(obj->vaoid));
	free(obj);
}

void	clean_mesh(t_mesh *mesh)
{
	t_obj		*obj;

	if (mesh->folder != NULL)
		free(mesh->folder);
	if (mesh->mtllib != NULL)
		free(mesh->mtllib);
	while (mesh->objs != NULL)
	{
		obj = mesh->objs;
		printf("clean obj : %s\n", obj->name);
		mesh->objs = mesh->objs->next;
		clean_obj(obj);
	}
	if (mesh->obj_vertex.v.vertices != NULL)
		free(mesh->obj_vertex.v.vertices);
	if (mesh->obj_vertex.vn.vertices != NULL)
		free(mesh->obj_vertex.vn.vertices);
	if (obj->vertex_data.vt.vertices != NULL)
		free(mesh->obj_vertex.vt.vertices);
	free(mesh);
}
