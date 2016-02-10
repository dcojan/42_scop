#include <scop.h>

void		init_sdl(t_sdl *sdl_var)
{
	printf("INIT_SDL\n");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	sdl_var->window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	sdl_var->context = SDL_GL_CreateContext(sdl_var->window);
	printf("done.\n");
}

void		init_gl(void)
{
	printf("INIT GL\n");
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	printf("done.\n");
}

void		init_glew(void)
{
	GLuint	vertex_buffer;

	printf("INIT_GLEW\n");
	glewExperimental = GL_TRUE;
	glewInit();
	glGenBuffers(1, &vertex_buffer);
	printf("done.\n");
}
