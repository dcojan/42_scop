/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:33 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/10 17:36:50 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_comment(t_mesh *mesh, FILE *stream, void *arg)
{
	int			ret;

	(void)arg;
	(void)mesh;
	printf("comment\n");
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
		mesh->mtllib = (char*)malloc(strlen(name) + strlen(mesh->folder) + 1);
		strcpy(mesh->mtllib, mesh->folder);
		mesh->mtllib = strcat(mesh->mtllib, name);
	}
	printf("%d =>  %s\n", ret, mesh->mtllib);
	consume_end_of_line(stream);
	load_mtl_obj_file(mesh->mtllib, &(mesh->material));
	return (ret);
}

int			label_usemtl(t_mesh *mesh, FILE *stream, void *arg)
{
	char	*name;
	int		ret;

	(void)arg;
	(void)mesh;
	name = NULL;
	printf("usemtl\t");
	if ((ret = getline(&name, (size_t*)&ret, stream)) == -1)
		perror("");
	if (ret != 0)
	{
		mesh->objs->usemtl = (t_material *)malloc(sizeof(t_material));
		mesh->objs->usemtl->name = NULL;
		mesh->objs->usemtl->next = NULL;
		mesh->objs->usemtl->name = name;
		mesh->objs->usemtl->name[ret - 1] = '\0';

	}
	printf("%d =>  %s\n", ret, mesh->objs->usemtl->name);
	// consume_end_of_line(stream);
	return (ret);
}

int			label_o(t_mesh *mesh, FILE *stream, void *arg)
{
	char	name[256];
	int		ret;
	t_obj	*obj;

	(void)arg;
	(void)mesh;
	printf("\nname\t");
	ret = fscanf(stream, "%s", name);
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
	consume_end_of_line(stream);
	return (ret);
}
