/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:33 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/15 22:25:16 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_comment(t_mesh *mesh, char *str, t_f_pos *arg)
{
	(void)arg;
	(void)mesh;
	printf("comment %s\n", str);
	return (1);
}

int			label_mtllib(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char	name[256];
	char	s[15];
	int		ret;

	(void)arg;
	printf("mtllib POUET %s\t", str);
	ret = sscanf(str, "%s %s", s, name);
	printf("ret = %d\n", ret);
	if (ret != 2)
	 	return (-1);
	mesh->mtllib = (char*)malloc(strlen(name) + strlen(mesh->folder) + 1);
	strcpy(mesh->mtllib, mesh->folder);
	mesh->mtllib = strcat(mesh->mtllib, name);
	printf("%d =>  %s\n", ret, mesh->mtllib);
	load_mtl_obj_file(mesh->mtllib, &(mesh->material));
	return (ret);
}

int			label_usemtl(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char	name[256];
	char	s[15];
	int		ret;

	(void)arg;
	(void)mesh;
	printf("usemtl\t");
	ret = sscanf(str, "%s %s", s, name);
	if (ret != 2)
	 	return (-1);
	if (ret == 2)
	{
		mesh->objs->usemtl = (t_material *)malloc(sizeof(t_material));
		mesh->objs->usemtl->name = NULL;
		mesh->objs->usemtl->next = NULL;
		mesh->objs->usemtl->name = strdup(name);
		printf("%d =>  %s\n", ret, mesh->objs->usemtl->name);
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
	printf("\nname\t");
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
	printf("%d =>  %s\n", ret, name);
	return (ret);
}
