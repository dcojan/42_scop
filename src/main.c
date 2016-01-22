#include <scop.h>


int		main(int ac, char **av)
{
	t_sdl				sdl_var;
	(void) ac;
	(void) av;
	init_sdl(&sdl_var);

	GLuint vertexArrayId;
	init_vao(&vertexArrayId);

	clean_sdl(&sdl_var);
	return (0);
}
