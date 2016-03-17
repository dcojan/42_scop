/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:33 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:40:49 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_comment(t_mesh *mesh, char *str, t_f_pos *arg)
{
	(void)arg;
	(void)mesh;
	printf("%s\n", str);
	return (1);
}

int			label_mtllib(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char	name[256];
	char	s[15];
	int		ret;

	(void)arg;
	ret = sscanf(str, "%s %s", s, name);
	if (ret != 2)
		return (-1);
	mesh->mtllib = (char*)malloc(strlen(name) + strlen(mesh->folder) + 1);
	strcpy(mesh->mtllib, mesh->folder);
	mesh->mtllib = strcat(mesh->mtllib, name);
	load_mtl_obj_file(mesh, mesh->mtllib);
	return (ret);
}

int			label_usemtl(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char		name[256];
	char		s[15];
	int			ret;
	t_material	*mat;

	(void)arg;
	ret = sscanf(str, "%s %s", s, name);
	if (ret != 2)
		return (-1);
	if (ret == 2)
	{
		mat = mesh->material;
		while (mat != NULL)
		{
			if (strcmp(mat->name, name) == 0)
			{
				mesh->objs->usemtl = mat;
				break ;
			}
			mat = mat->next;
		}
	}
	return (ret);
}

int			label_o(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char	name[256];
	char	s[15];
	int		ret;
	t_obj	*obj;

	(void)arg;
	(void)mesh;
	ret = sscanf(str, "%s %s", s, name);
	if (ret != 2)
		return (-1);
	if (mesh->objs->name == NULL)
		mesh->objs->name = strdup(name);
	else
	{
		obj = new_obj();
		obj->next = mesh->objs;
		mesh->objs = obj;
		mesh->objs->name = strdup(name);
	}
	return (ret);
}
