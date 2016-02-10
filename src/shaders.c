#include <scop.h>

void	compile_shader(const GLchar *buf, const GLuint *prog, const GLenum type)
{
	GLuint		id;
	char		error_message[2048];
	GLint		result;
	GLint		log_length;

	result = GL_FALSE;
	id = glCreateShader(type);
	glShaderSource(id, 1, &buf, NULL);
	glCompileShader(id);
	log_length = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		printf("Shader compilation failed\n");
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length > 0)
		{
			glGetShaderInfoLog(id, log_length, NULL, error_message);
			error_message[log_length] = '\0';
			printf("VertexShaderError : \n%s\n", error_message);
		}
	}
	glAttachShader(*prog, id);
	glLinkProgram(*prog);
	glDeleteShader(id);
}

void	new_shader(const char *path, const GLuint *program, const GLenum type)
{
	char		*source;

	glsl_loader(&source, path);
	compile_shader(source, program, type);
	free(source);
}

GLuint	load_shaders(void)
{
	char		error_message[2048];
	GLint		result;
	int			log_length;
	GLuint		program;

	program = glCreateProgram();
	new_shader("glsl/vertex_shader.glsl", &program, GL_VERTEX_SHADER);
	new_shader("glsl/fragment_shader.glsl", &program, GL_FRAGMENT_SHADER);
	result = GL_FALSE;
	log_length = 0;
	glGetShaderiv(program, GL_COMPILE_STATUS, &result);
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0)
	{
		glGetProgramInfoLog(program, log_length, NULL, error_message);
		printf("ProgramShaderError :\n%s\n", error_message);
	}
	return (program);
}
