#ifndef OBJECT_LOADER_H
# define OBJECT_LOADER_H

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

typedef struct		s_obj
{
	t_vertex_data	vertex_data;
	t_element_data	elements;
	uint32_t		vertexBuffer;
	uint32_t		normalBuffer;
	uint32_t		shaderProgram;
}					t_obj;

t_obj    	*load_obj(char *path);
int			consume_end_of_line(FILE *stream);

void		add_vec3(t_vec3 *vec, t_vertex *v);
void		add_element(GLushort *el, t_element *v, int nb);
t_obj		*new_obj();
void		compute_normals(t_obj *obj);
void		unpack_elements(t_obj *obj);

int			parse_label(t_obj *obj, FILE *stream);
int			label_usemtl(t_obj *obj, FILE *stream);
int			label_mtllib(t_obj *obj, FILE *stream);
int			label_comment(t_obj *obj, FILE *stream);
int			label_f(t_obj *obj, FILE *stream);
int			label_s(t_obj *obj, FILE *stream);
int			label_o(t_obj *obj, FILE *stream);
int			label_v(t_obj *obj, FILE *stream);

void    	print_element_array(GLushort *array, size_t size);
void    	print_vertice_array(GLfloat *array, size_t size);
#endif
