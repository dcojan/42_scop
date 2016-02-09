#include <scop.h>

void compile_shader(const GLchar *text, const GLuint *program, const GLenum type)
{
	GLuint     id;
    char        VertexShaderErrorMessage[2048];
    GLint       Result;
    GLint         InfoLogLength;

    Result = GL_FALSE;
    id = glCreateShader(type);
	glShaderSource(id, 1, &text, NULL);
	glCompileShader(id);

    InfoLogLength = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE)
	{
		printf("Shader compilation failed\n");
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		printf("InfoLogLength : %d\n", InfoLogLength);
		if (InfoLogLength > 0){
			glGetShaderInfoLog(id, InfoLogLength, NULL, VertexShaderErrorMessage);
			VertexShaderErrorMessage[InfoLogLength] = '\0';
			printf("VertexShaderError : \n%s\n", VertexShaderErrorMessage);
		}
	}
	glAttachShader(*program, id);
	glLinkProgram(*program);

    glDeleteShader(id);
}

GLuint loadShaders()
{
	char        ProgramErrorMessage[2048];
	GLint       Result;
	int         InfoLogLength;
	GLuint		program;
	char		*source;

	program = glCreateProgram();
	glsl_loader(&source, "glsl/vertex_shader.glsl");
	compile_shader(source, &program, GL_VERTEX_SHADER);
	free(source);

	glsl_loader(&source, "glsl/fragment_shader.glsl");
	compile_shader(source, &program, GL_FRAGMENT_SHADER);
	free(source);

	Result = GL_FALSE;
	InfoLogLength = 0;
	glGetShaderiv(program, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		glGetProgramInfoLog(program, InfoLogLength, NULL, ProgramErrorMessage);
		printf("ProgramShaderError :\n%s\n", ProgramErrorMessage);
	}
	return program;
}
