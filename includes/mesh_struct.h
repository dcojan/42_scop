
# include "glmath.h"

typedef struct		s_vertex
{
	float			*vertices;
	size_t			size;
}					t_vertex;

typedef struct		s_element
{
	GLushort		*element;
	size_t			size;
}					t_element;

typedef struct		s_vertex_data
{
	t_vertex		v;
	t_vertex		vt;
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
	t_element		vn;
	t_element		vt;
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

typedef struct		s_obj
{
	GLuint			vaoid;
	uint32_t		shader_program;
	char			*name;
	t_vertex_data	tmp_vert;
	t_vertex_data	vertex_data;
	t_element_data	elements;
	t_vec3			origin;
	t_material		*usemtl;
	uint32_t		vertex_buffer;
	uint32_t		normal_buffer;
	uint32_t		texture_buffer;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_mesh
{
	char			*folder;
	t_vertex_data	obj_vertex;
	char			*mtllib;
	t_obj			*objs;
	uint32_t		shader_program;
}					t_mesh;

// typedef struct		s_mesh
// {
// 	char			*folder;
// 	t_vertex_data	vertex_data;
// 	t_element_data	elements;
// 	t_vec3			origin;
// 	t_material_lib	mtl_lib;
// 	uint32_t		vertex_buffer;
// 	uint32_t		normal_buffer;
// 	uint32_t		texture_buffer;
// 	uint32_t		shader_program;
// }					t_mesh;
