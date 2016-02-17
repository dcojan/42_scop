/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:33 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/17 17:31:56 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

int			label_comment(t_mesh *mesh, FILE *stream)
{
	int			ret;

	(void)mesh;
	printf("comment\t");
	ret = consume_end_of_line(stream);
	return (ret);
}

int			label_mtllib(t_mesh *mesh, FILE *stream)
{
	char	name[256];
	int		ret;

	printf("mtllib\t");
	ret = fscanf(stream, "%s", name);
	if (ret != 0)
	{
		mesh->mtl_lib.path = strdup(name);
	}
	printf("%d =>  %s\n", ret, mesh->mtl_lib.path);
	consume_end_of_line(stream);
	return (ret);
}

int			label_usemtl(t_mesh *mesh, FILE *stream)
{
	char	name[256];
	int		ret;

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

int			label_o(t_mesh *mesh, FILE *stream)
{
	char	name[256];
	int		ret;

	(void)mesh;
	printf("name\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	consume_end_of_line(stream);
	return (ret);
}
