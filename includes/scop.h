#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <GL/gl.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>

# define WIDTH  		800
# define HEIGHT 		600

typedef struct		s_sdl
{
	SDL_Window* window;
	SDL_GLContext context;
}					        t_sdl;

void		init_sdl(t_sdl *sdl_var);
void		clean_sdl(t_sdl *sdl_var);

#endif
