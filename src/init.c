#include <scop.h>

void		init_sdl(t_sdl *sdl_var)
{
    printf("A\n");
    SDL_Init(SDL_INIT_VIDEO);
    printf("B\n");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    printf("C\n");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    printf("D\n");
	sdl_var->window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    printf("E\n");
	sdl_var->context = SDL_GL_CreateContext(sdl_var->window);
}

void        init_gl(){
    glFrontFace( GL_CCW );
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST); //doesn't change a thing
    glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
}

void		init_glew()
{
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
}
