#include <scop.h>

void		init_sdl(t_sdl *sdl_var)
{
    SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	sdl_var->window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	sdl_var->context = SDL_GL_CreateContext(sdl_var->window);
}

void        init_gl(){
    glFrontFace( GL_CCW );
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST); //doesn't change a thing
    glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
}

void    init_vao(GLuint *vertexArrayId)
{
    glGenVertexArrays(1, vertexArrayId);
    glBindVertexArray(*vertexArrayId);
}

void		init_glew()
{
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
}

const GLfloat g_vertex_buffer_data[] = {

    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end

    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end

    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,

    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,

    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

// static const GLfloat g_vertex_buffer_data[] = {
//    -1.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 0.0f,
//    0.0f,  1.0f, 0.0f,
// };

GLuint  init_vertex_buffer()
{
  	GLuint vertexBuffer;
  	glGenBuffers(1, &vertexBuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  	glEnableVertexAttribArray(0);
    return vertexBuffer;
}
//
// GLuint  init_texture_buffer()
// {
//   	GLuint vertexBuffer;
//   	glGenBuffers(1, &vertexBuffer);
//   	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//   	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
//   	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
//   	glEnableVertexAttribArray(1);
//     return vertexBuffer;
// }
