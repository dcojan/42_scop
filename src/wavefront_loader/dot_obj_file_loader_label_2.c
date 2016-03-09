/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:33 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 11:57:27 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_comment(t_mesh *mesh, FILE *stream, void *arg)
{
	int			ret;

	(void)arg;
	(void)mesh;
	printf("comment\t");
	ret = consume_end_of_line(stream);
	return (ret);
}

int			label_mtllib(t_mesh *mesh, FILE *stream, void *arg)
{
	char	name[256];
	int		ret;

	(void)arg;
	printf("mtllib\t");
	ret = fscanf(stream, "%s", name);
	if (ret != 0)
	{
		mesh->mtl_lib.path = (char*)malloc(strlen(name) + strlen(mesh->folder));
		strcpy(mesh->mtl_lib.path, mesh->folder);
		mesh->mtl_lib.path = strcat(mesh->mtl_lib.path, name);
	}
	printf("%d =>  %s\n", ret, mesh->mtl_lib.path);
	consume_end_of_line(stream);
	return (ret);
}

int			label_usemtl(t_mesh *mesh, FILE *stream, void *arg)
{
	char	name[256];
	int		ret;

	(void)arg;
	(void)mesh;
	printf("usemtl\t");
	ret = fscanf(stream, "%s", name);
	if (ret != 0)
	{
		mesh->mtl_lib.material = (t_material *)malloc(sizeof(t_material));
		mesh->mtl_lib.material->name = NULL;
		mesh->mtl_lib.material->next = NULL;
		mesh->mtl_lib.material->name = strdup(name);
	}
	printf("%d =>  %s\n", ret, mesh->mtl_lib.material->name);
	consume_end_of_line(stream);
	return (ret);
}

int			label_o(t_mesh *mesh, FILE *stream, void *arg)
{
	char	name[256];
	int		ret;

	(void)arg;
	(void)mesh;
	printf("name\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	consume_end_of_line(stream);
	return (ret);
}
