/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_mtl_file_loader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:36:16 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/10 18:36:50 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int	mtl_label_comment(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_empty(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_newmtl(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_ns(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_ka(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_kd(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_ks(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_ni(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_d(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_illum(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_map_kd(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_map_bump(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}

int	mtl_label_map_ks(t_material **mtl, FILE *stream, void*arg)
{
	(void)mtl;
	(void)stream;
	(void)arg;
	return (1);
}


static int	(*const g_func_tab[13])(t_material **mtl, FILE *stream, void *arg) =
{
	&mtl_label_comment,
	&mtl_label_empty,
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

t_material	*new_material()
{
	t_material		*mat;

	mat = (t_material*)malloc(sizeof(t_material));
	mat->name = NULL;
	mat->next = NULL;
	mat->map_kd = NULL;
	mat->map_bump = NULL;
	mat->map_ks = NULL;
	return (mat);
}

static int	parse_label(t_material **mtl, FILE *stream)
{
	char		label[32];
	int			ret;
	static char	*tab[13] = { "#", "/n",
		"newmtl", "Ns", "Ka", "Kd", "Ks", "Ni", "d", "illum", "map_Kd",
		"map_Bump", "map_Ks"
	};
	int			i;

	ret = fscanf(stream, "%s", label);
	if (ret == EOF)
		return (0);
	i = 0;
	while (i < 13)
	{
		if (strcmp(tab[i], label) == 0)
			return (*g_func_tab[i])(mtl, stream, NULL);
		i++;
	}
	return (1);
}

int		load_mtl_obj_file(char *path, t_material **mtl)
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
		ret = parse_label(mtl, stream);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (0);
	}
	fclose(stream);
	return (1);
}
