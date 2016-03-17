/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 15:52:50 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

void		label_f_(t_f_pos *face_pos, int tmp[3], GLushort *el, int ret2)
{
	el[0] = (tmp[0] < 0 ? face_pos->v + 1 + tmp[0] : tmp[0]);
	if (ret2 == 3 || ret2 == 2)
		el[4] = (tmp[1] < 0 ? face_pos->vt + 1 + tmp[1] : tmp[1]);
	if (ret2 == 3 || ret2 == 4)
		el[8] = (tmp[2] < 0 ? face_pos->vn + 1 + tmp[2] : tmp[2]);
}

int			label_f(t_mesh *mesh, char *str, t_f_pos *face_pos)
{
	int			ret[2];
	GLushort	el[12];
	int			tmp[3];
	char		s[4][64];
	int			i;

	str = &(str[1]);
	if ((ret[0] = sscanf(str, " %s %s %s %s", s[0], s[1], s[2], s[3])) < 3)
		return (-1);
	ret[1] = 0;
	i = 0;
	while (i < ret[0])
	{
		ret[1] = sscanf(s[i], " %d/%d/%d", &(tmp[0]), &(tmp[1]), &(tmp[2]));
		if (ret[1] == 1)
			ret[1] += 3 * sscanf(s[i], " %*d//%d", &(tmp[2]));
		label_f_(face_pos, tmp, &(el[i]), ret[1]);
		i++;
	}
	add_element(el, &(mesh->objs->elements.f), ret[0]);
	if (ret[1] == 3 || ret[1] == 2)
		add_element(&(el[4]), &(mesh->objs->elements.vt), ret[0]);
	if (ret[1] == 3 || ret[1] == 4)
		add_element(&(el[8]), &(mesh->objs->elements.vn), ret[0]);
	return (ret[0]);
}

int			label_v(t_mesh *mesh, char *str, t_f_pos *face_pos)
{
	t_vec3		v;
	int			ret;

	face_pos->v++;
	str = &(str[1]);
	ret = sscanf(str, " %f %f %f", &(v.data[0]), &(v.data[1]), &(v.data[2]));
	if (ret < 3)
		return (-1);
	add_vec3(&v, &(mesh->obj_vertex.v));
	return (ret);
}

int			label_vn(t_mesh *mesh, char *str, t_f_pos *face_pos)
{
	t_vec3		v;
	int			ret;

	str = &(str[2]);
	face_pos->vn++;
	ret = sscanf(str, " %f %f %f", &(v.data[0]), &(v.data[1]), &(v.data[2]));
	if (ret < 3)
		return (-1);
	add_vec3(&v, &(mesh->obj_vertex.vn));
	return (ret);
}

int			label_vt(t_mesh *mesh, char *str, t_f_pos *face_pos)
{
	t_vec3		v;
	int			ret;

	str = &(str[2]);
	face_pos->vt++;
	ret = sscanf(str, " %f %f", &(v.data[0]), &(v.data[1]));
	if (ret < 2)
		return (0);
	add_vec2(&v, &(mesh->obj_vertex.vt));
	return (ret);
}
