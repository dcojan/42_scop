#include <scop.h>

void	clean_sdl(t_sdl *sdl_var)
{
	SDL_GL_DeleteContext(sdl_var->context);
    SDL_Quit();
}
