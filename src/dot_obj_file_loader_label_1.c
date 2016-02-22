/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:20:16 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static int	(*const g_func_tab[7])(t_mesh *mesh, FILE *stream) =
{
	&label_comment,
	&label_v,
	&label_f,
	&label_o,
	&label_s,
	&label_mtllib,
	&label_usemtl,
};

int			parse_label(t_mesh *mesh, FILE *stream)
{
	static char		*tab[7] = {"#", "v", "f", "o", "s", "mtllib", "usemtl"};
	int				i;
	char			label[15];
	int				ret;

	ret = fscanf(stream, "%s", label);
	if (ret == EOF)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (strcmp(tab[i], label) == 0)
			return (*g_func_tab[i])(mesh, stream);
		i++;
	}
	printf("parse error state `%s` not recognized\n", label);
	return (-1);
}

int			label_f(t_mesh *mesh, FILE *stream)
{
	int			ret;
	GLushort	el[4];

	ret = fscanf(stream, " %hd %hd %hd %hd",
		&(el[0]), &(el[1]), &(el[2]), &(el[3]));
	add_element(el, &(mesh->elements.f), ret);
	return (ret);
}

int			label_s(t_mesh *mesh, FILE *stream)
{
	int		ret;
	char	name[256];

	(void)mesh;
	printf("smoothing group\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	return (ret);
}

int			label_v(t_mesh *mesh, FILE *stream)
{
	t_vec3		v;
	int			ret;

	ret = fscanf(stream, " %f %f %f", &(v.data[0]), &(v.data[1]), &(v.data[2]));
	add_vec3(&v, &(mesh->vertex_data.v));
	return (ret);
}
