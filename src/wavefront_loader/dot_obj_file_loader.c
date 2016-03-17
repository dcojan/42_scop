/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:36:11 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

static int	(*const g_tab[11])(t_mesh *mesh, char *str, t_f_pos *arg) =
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
	size_t			i;
	char			label[15];
	int				ret;
	char			*str;

	str = NULL;
	if ((ret = getline(&str, &i, stream)) == -1)
		return (0);
	if (str[0] == '\n')
		return (1);
	if (ret > 0)
		str[ret - 1] = '\0';
	ret = sscanf(str, "%s", label);
	i = 0;
	ret = -1;
	while (i < 11)
	{
		if (strcmp(tab[i], label) == 0)
			ret = (*g_tab[i])(mesh, str, face_pos);
		i++;
	}
	free(str);
	return (ret);
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
	printf("Loading object from file %s\n", path);
	if ((stream = open_file(path)) == NULL)
		return (NULL);
	mesh->folder = make_folder_path(path);
	while ((ret = parse_label(mesh, stream, &face_pos)) > 0)
		;
	if (ret == -1)
	{
		printf("parse error : label not recognized\n");
		return (NULL);
	}
	fclose(stream);
	printf("Done.\n");
	return (mesh);
}
