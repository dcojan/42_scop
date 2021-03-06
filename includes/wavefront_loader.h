/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavefront_loader.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:01:17 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 11:26:43 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAVEFRONT_LOADER_H
# define WAVEFRONT_LOADER_H

# include "mesh_struct.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef	enum		e_label
{
	LABEL_COMMENT,
	LABEL_V,
	LABEL_VN,
	LABEL_F,
	LABEL_O,
	LABEL_S,
	LABEL_G,
	LABEL_MTLLIB,
	LABEL_USEMTL,
	LABEL_NONE,
}					t_label;

typedef struct		s_f_pos
{
	t_label			last;
	int				v;
	int				vt;
	int				vn;
}					t_f_pos;

t_mesh				*load_dot_obj_file(t_mesh *mesh, char *path);
int					load_mtl_obj_file(t_mesh *mesh, char *path);

int					label_usemtl(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_mtllib(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_comment(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_f(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_s(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_o(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_v(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_vn(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_vt(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_g(t_mesh *mesh, char *str, t_f_pos *arg);
int					label_l(t_mesh *mesh, char *str, t_f_pos *arg);

t_mesh				*new_mesh(void);
t_obj				*new_obj(void);
char				*make_folder_path(char *file);
FILE				*open_file(const char *path);
int					consume_end_of_line(FILE *stream);
void				add_vec3(t_vec3 *vec, t_vertex *v);
void				add_vec2(t_vec3 *vec, t_vertex *v);
void				add_element(GLushort *el, t_element *v, int nb);
void				print_element_array(GLushort *array, size_t size);
void				print_vertice_array(GLfloat *array, size_t size);

t_material			*new_material();
int					mtl_label_comment(t_mesh *mesh, char *str, void*arg);
int					mtl_label_newmtl(t_mesh *mesh, char *str, void*arg);
int					mtl_label_ns(t_mesh *mesh, char *str, void*arg);
int					mtl_label_ka(t_mesh *mesh, char *str, void*arg);
int					mtl_label_kd(t_mesh *mesh, char *str, void*arg);
int					mtl_label_ks(t_mesh *mesh, char *str, void*arg);
int					mtl_label_ni(t_mesh *mesh, char *str, void*arg);
int					mtl_label_d(t_mesh *mesh, char *str, void*arg);
int					mtl_label_illum(t_mesh *mesh, char *str, void*arg);
int					mtl_label_map_kd(t_mesh *mesh, char *str, void*arg);

#endif
