#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include <glmath.h>
# include <stdio.h>

# define WIDTH  		800
# define HEIGHT 		600

typedef enum 		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct		s_sdl
{
	SDL_Window* window;
	SDL_GLContext context;
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
}					t_obj;


void		init_sdl(t_sdl *sdl_var);
void		init_glew();
void    	init_vao(GLuint *vertexArrayId);
void		init_gl();
GLuint		init_vertex_buffer(t_obj *obj);
GLuint		init_normal_buffer(t_obj *obj);

GLuint 		init_element_array_buffer(t_obj *obj);

GLuint		loadShaders();
t_obj    	*load_obj(char *path);


void 		main_loop(t_sdl	*sdl_var,GLuint shaderProgram, t_obj *obj);
void		init_camera();


void		clean_sdl(t_sdl *sdl_var);

#endif
