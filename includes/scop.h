#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include <glmath.h>
# include <stdio.h>
# include <fcntl.h>

# define WIDTH  		800
# define HEIGHT 		600

typedef enum 		e_bool
{
	FALSE,
	TRUE
}					t_bool;


typedef struct		s_sdl
{
	SDL_Window*		window;
	SDL_GLContext	context;
}					t_sdl;

typedef struct		s_vertex
{
	GLfloat			*vertices;
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
	GLuint			vertexBuffer;
	GLuint			normalBuffer;
	GLuint			shaderProgram;
}					t_obj;


void		init_sdl(t_sdl *sdl_var);
void		init_glew();
void		init_gl();
// GLuint		init_vertex_buffer(t_obj *obj);
// GLuint		init_normal_buffer(t_obj *obj);
GLuint  	new_buffer(GLuint type, GLuint size, GLfloat *vertices, GLuint draw);

void		scop(t_obj *obj, t_sdl *sdl_var);

GLuint 		init_element_array_buffer(t_obj *obj);
int			glsl_loader(char **text, const char *path);

GLuint		load_shaders();
FILE		*open_file(const char *path);
t_obj    	*load_obj(char *path);
int			consume_end_of_line(FILE *stream);

void		set_camera(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLuint shaderProgram);
void		set_light(GLfloat lightX, GLfloat lightY, GLfloat lightZ, GLuint shaderProgram);

void 		main_loop(t_sdl	*sdl_var,GLuint shaderProgram, t_obj *obj);

void		clean_sdl(t_sdl *sdl_var);
void    	print_element_array(GLushort *array, size_t size);
void    	print_vertice_array(GLfloat *array, size_t size);

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

#endif
