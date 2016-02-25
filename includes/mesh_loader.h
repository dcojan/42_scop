/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_loader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:01:17 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 10:10:07 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_LOADER_H
# define MESH_LOADER_H

# include "glmath.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_vertex
{
	float			*vertices;
	size_t			size;
}					t_vertex;

typedef struct		s_element
{
	unsigned short	*element;
	size_t			size;
}					t_element;

typedef struct		s_vertex_data
{
	t_vertex		v;
	void			*vt;
	t_vertex		vn;
	void			*vp;
	void			*cstype;
	void			*deg;
	void			*bmat;
	void			*step;
}					t_vertex_data;

typedef struct		s_element_data
{
	void			*p;
	void			*l;
	t_element		f;
	void			*curv;
	void			*curv2;
	void			*surf;
}					t_element_data;

typedef	struct		s_material
{
	char				*name;
	float				ns;
	t_vec3				ka;
	t_vec3				kd;
	t_vec3				ks;
	float				ni;
	uint8_t				d;
	struct s_material	*next;
}					t_material;

typedef	struct		s_material_lib
{
	char			*path;
	t_material		*material;
}					t_material_lib;

typedef struct		s_mesh
{
	char			*folder;
	t_vertex_data	vertex_data;
	t_element_data	elements;
	t_vec3			origin;
	t_material_lib	mtl_lib;
	uint32_t		vertex_buffer;
	uint32_t		normal_buffer;
	uint32_t		texture_buffer;
	uint32_t		shader_program;
}					t_mesh;

void				load_mtl_obj_file(t_mesh *mesh);
t_mesh				*load_dot_obj_file(char *path);
int					consume_end_of_line(FILE *stream);
void				add_vec3(t_vec3 *vec, t_vertex *v);
void				add_element(GLushort *el, t_element *v, int nb);
t_mesh				*new_mesh();
void				clean_mesh(t_mesh *mesh);
void				compute_normals(t_mesh *mesh);
void				unpack_elements(t_mesh *mesh);
int					parse_label(t_mesh *mesh, FILE *stream);
int					label_usemtl(t_mesh *mesh, FILE *stream);
int					label_mtllib(t_mesh *mesh, FILE *stream);
int					label_comment(t_mesh *mesh, FILE *stream);
int					label_f(t_mesh *mesh, FILE *stream);
int					label_s(t_mesh *mesh, FILE *stream);
int					label_o(t_mesh *mesh, FILE *stream);
int					label_v(t_mesh *mesh, FILE *stream);
void				print_element_array(GLushort *array, size_t size);
void				print_vertice_array(GLfloat *array, size_t size);
#endif
