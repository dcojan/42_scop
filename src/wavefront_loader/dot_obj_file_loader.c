/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:40 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/15 22:37:01 by nhiboux          ###   ########.fr       */
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
	{
		perror("");
		return (0);
	}
	// printf("ret = %d - PARSE str %s\n", ret, str);
	if (str[0] == '\n')
		return (1);
	if (ret > 0)
		str[ret - 1] = '\0';
	ret = sscanf(str, "%s", label);
	// printf("PARSE ret %d\n", ret);
	// printf("PARSE label %s\n", label);
	i = 0;
	while (i < 11)
	{
		if (strcmp(tab[i], label) == 0)
		{
			// printf("PARSER face_pos address %p\n", face_pos);
			return (*g_tab[i])(mesh, str, face_pos);
		}
		i++;
	}
	free(str);
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
	// printf("face_pos address %p\n", &face_pos);
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
	fclose(stream);
	printf("Done.\n");
	return (mesh);
}
