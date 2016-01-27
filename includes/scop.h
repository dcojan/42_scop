#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>

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

void		init_sdl(t_sdl *sdl_var);
void		init_glew();
void    	init_vao(GLuint *vertexArrayId);
void		init_gl();
GLuint		loadShaders();


void 		main_loop(t_sdl	*sdl_var);


void		clean_sdl(t_sdl *sdl_var);

#endif
