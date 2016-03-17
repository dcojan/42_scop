/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:36:16 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 15:58:27 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			mtl_label_map_bump(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int			mtl_label_map_ks(t_mesh *mesh, char *str, void *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

static int	(*const g_mtl_tab[12])(t_mesh *, char *, void *) =
{
	&mtl_label_comment,
	&mtl_label_newmtl,
	&mtl_label_ns,
	&mtl_label_ka,
	&mtl_label_kd,
	&mtl_label_ks,
	&mtl_label_ni,
	&mtl_label_d,
	&mtl_label_illum,
	&mtl_label_map_kd,
	&mtl_label_map_bump,
	&mtl_label_map_ks,
};

static int	parse_label(t_mesh *mesh, FILE *stream)
{
	static char		*tab[12] = { "#", "newmtl", "Ns", "Ka", "Kd", "Ks", "Ni",
		"d", "illum", "map_Kd", "map_Bump", "map_Ks"};
	char			label[32];
	int				ret;
	size_t			i;
	char			*str;

	bzero(label, 32);
	str = NULL;
	if ((ret = getline(&str, &i, stream)) == -1)
		return (0);
	if (str[0] == '\n')
		return (1);
	if (ret > 0)
		str[ret - 1] = '\0';
	ret = sscanf(str, "%s", label);
	i = 0;
	while (i < 12)
	{
		if (strcmp(tab[i], label) == 0)
			return (*g_mtl_tab[i])(mesh, str, NULL);
		i++;
	}
	return (0);
}

int			load_mtl_obj_file(t_mesh *mesh, char *path)
{
	FILE		*stream;
	ssize_t		ret;
	char		*buf;

	buf = NULL;
	printf("Loading %s\n", path);
	if ((stream = open_file(path)) == NULL)
		return (0);
	while (1)
	{
		ret = parse_label(mesh, stream);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (0);
	}
	fclose(stream);
	return (1);
}
