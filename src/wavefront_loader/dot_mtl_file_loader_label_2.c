/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:54:44 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 15:19:39 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int	mtl_label_ks(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_ni(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_d(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_illum(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_map_kd(t_mesh *mesh, char *str, void *arg)
{
	char	name[255];
	char	l[35];
	int		ret;
	int		size;

	(void)arg;
	ret = sscanf(str, "%s %s", l, name);
	size = strlen(name) + strlen(mesh->folder) + 1;
	mesh->material->map_kd = (char*)malloc(size);
	strcpy(mesh->material->map_kd, mesh->folder);
	mesh->material->map_kd = strcat(mesh->material->map_kd, name);
	printf("map_kd : %s\n", mesh->material->map_kd);
	return (1);
}
