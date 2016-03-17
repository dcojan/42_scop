/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader_label_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:52:51 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:07:58 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int	mtl_label_comment(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_newmtl(t_mesh *mesh, char *str, void *arg)
{
	char		name[225];
	char		l[35];
	int			ret;
	t_material	*mtl;

	(void)mesh;
	printf("newmtl\n");
	ret = sscanf(str, "%s %s", l, name);
	if (ret != 2)
		return (-1);
	mtl = new_material();
	mtl->name = strdup(name);
	mtl->next = mesh->material;
	mesh->material = mtl;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_ns(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_ka(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int	mtl_label_kd(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}
