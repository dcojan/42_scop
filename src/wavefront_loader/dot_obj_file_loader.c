/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 19:43:46 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

static int	(*const g_func_tab[11])(t_mesh *mesh, FILE *stream, void *arg) =
{
	&label_comment,
	&label_v,
	&label_vn,
	&label_vt,
	&label_f,
	&label_o,
	&label_s,
	&label_g,
	&label_l,
	&label_mtllib,
	&label_usemtl,
};

static int	parse_label(t_mesh *mesh, FILE *stream, t_f_pos *face_pos)
{
	static char		*tab[11] = {
		"#", "v", "vn", "vt", "f", "o", "s", "g", "l", "mtllib", "usemtl"};
	int				i;
	char			label[15];
	int				ret;

	ret = fscanf(stream, "%s", label);
	if (ret == EOF)
		return (0);
	i = 0;
	while (i < 11)
	{
		if (strcmp(tab[i], label) == 0)
			return (*g_func_tab[i])(mesh, stream, face_pos);
		i++;
	}
	printf("parse error state `%s` not recognized\n", label);
	return (-1);
}

t_mesh		*load_dot_obj_file(t_mesh *mesh, char *path)
{
	FILE		*stream;
	int			ret;
	t_f_pos		face_pos;

	face_pos.last = LABEL_NONE;
	face_pos.v = 0;
	face_pos.vt = 0;
	face_pos.vn = 0;
	printf("Loading %s\n", path);
	if ((stream = open_file(path)) == NULL)
		return (NULL);
	mesh->folder = make_folder_path(path);
	printf("Loading object from file\n");
	while (1)
	{
		ret = parse_label(mesh, stream, &face_pos);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (NULL);
	}
	printf("Done.\n");
	return (mesh);
}
