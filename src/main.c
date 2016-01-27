#include <scop.h>


int		main(int ac, char **av)
{
	t_sdl				sdl_var;
	(void) ac;
	(void) av;
	init_sdl(&sdl_var);
	init_glew();
	init_gl();

	GLuint vertexArrayId;
	init_vao(&vertexArrayId);

	main_loop(&sdl_var);

	clean_sdl(&sdl_var);
	return (0);
}
