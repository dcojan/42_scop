/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/15 17:45:28 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_l(t_mesh *mesh, FILE *stream, void *arg)
{
	char		*buf;
	int			tmp;
	int			ret;

	(void)mesh;
	(void)arg;
	buf = NULL;
	// printf("label_l\t");
	if ((ret = getline(&buf, (size_t*)&tmp, stream)) == -1)
		perror("");
	// printf("%d =>  %s\n", ret, buf);
	free(buf);
	return (ret);
}

int			label_g(t_mesh *mesh, FILE *stream, void *arg)
{
	char	name[256];
	int		ret;

	(void)arg;
	(void)mesh;
	printf("group\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	consume_end_of_line(stream);
	return (ret);
}

int			label_f(t_mesh *mesh, FILE *stream, void *arg)
{
	int			ret;
	int			ret2;
	GLushort	el[12];
	int			tmp[3];
	char		s[4][64];
	char		*buf;
	t_f_pos		*face_pos;

	buf = NULL;
	face_pos = (t_f_pos *)arg;
	if ((ret = getline(&buf, (size_t*)&tmp, stream)) == -1)
		perror("");
	ret = sscanf(buf, " %s %s %s %s", s[0], s[1], s[2], s[3]);
	int i = 0;
	// if ret < 3 : exit error
	ret2 = 0;
	while (i < ret)
	{
		ret2 = sscanf(s[i], " %d/%d/%d", &(tmp[0]), &(tmp[1]), &(tmp[2]));
		if (ret2 == 1)
			ret2 += 3 * sscanf(s[i], " %*d//%d", &(tmp[2]));
			el[i] = (tmp[0] < 0 ? face_pos->v + 1 + tmp[0] : tmp[0]);
		if (ret2 == 3 || ret2 == 2) // v/vt/vn
			el[i + 4] = (tmp[1] < 0 ? face_pos->vt + 1 + tmp[1] : tmp[1]);
		if (ret2 == 3 || ret2 == 4) // v/vt/
			el[i + 8] = (tmp[2] < 0 ? face_pos->vn + 1 + tmp[2] : tmp[2]);
		i++;
	}
	// printf("el0 = %d\n", el[0]);
	// printf("el1 = %d\n", el[1]);
	// printf("el2 = %d\n", el[2]);
	// printf("el3 = %d\n", el[3]);
	add_element(el, &(mesh->objs->elements.f), ret);
	if (ret2 == 3 || ret2 == 2)
		add_element(&(el[4]), &(mesh->objs->elements.vt), ret);
	if (ret2 == 3 || ret2 == 4)
		add_element(&(el[8]), &(mesh->objs->elements.vn), ret);
	free(buf);
	return (ret);
}

int			label_s(t_mesh *mesh, FILE *stream, void *arg)
{
	int		ret;
	char	name[256];

	(void)mesh;
	(void)arg;
	printf("smoothing group\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	return (ret);
}

int			label_v(t_mesh *mesh, FILE *stream, void *arg)
{
	t_vec3		v;
	int			ret;
	t_f_pos		*face_pos;

	face_pos = (t_f_pos *)arg;
	face_pos->v++;
	ret = fscanf(stream, " %f %f %f", &(v.data[0]), &(v.data[1]), &(v.data[2]));
	// printf("%s = %f %f %f -> %zu\n", mesh->objs->name, v.data[0], v.data[1], v.data[2], mesh->objs->vertex_data.v.size);
	// add_vec3(&v, &(mesh->objs->vertex_data.v));
	add_vec3(&v, &(mesh->obj_vertex.v));
	// printf("DONE\n");
	return (ret);
}

int			label_vn(t_mesh *mesh, FILE *stream, void *arg)
{
	t_vec3		v;
	int			ret;
	t_f_pos		*face_pos;

	face_pos = (t_f_pos *)arg;
	face_pos->vn++;
	// printf("label_vn\n");
	ret = fscanf(stream, " %f %f %f", &(v.data[0]), &(v.data[1]), &(v.data[2]));
	// add_vec3(&v, &(mesh->objs->vertex_data.vn));
	add_vec3(&v, &(mesh->obj_vertex.vn));
	return (ret);
}

int			label_vt(t_mesh *mesh, FILE *stream, void *arg)
{
	t_vec3		v;
	int			ret;
	t_f_pos		*face_pos;

	face_pos = (t_f_pos *)arg;
	face_pos->vt++;
	ret = fscanf(stream, " %f %f", &(v.data[0]), &(v.data[1]));
	// add_vec3(&v, &(mesh->objs->vertex_data.vt));
	add_vec2(&v, &(mesh->obj_vertex.vt));
	return (ret);
}
