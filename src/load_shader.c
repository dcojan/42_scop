#include <scop.h>

const GLchar		vertexSource[] =
	"#version 330 core\n"
	"layout(location = 0) in vec3 in_vertex;"
    // "layout(location = 1) in vec3 vertexColor;"
	// "vec3 vertexColor = vec3(1.0f,0.0f,0.0f);"
	// "layout(location = 1) in vec2 vertexUV;"
	"uniform mat4 MVP;"

	// "out vec3 fragmentColor;"
	// "out vec2 UV;"

	"void main() {"
	// "	fragmentColor = vertexColor;"
	// "UV = vertexUV;"
	"  float scale = 1.0;"
 	"   mat4 pos = mat4(1.0f);"
    // " gl_Position = MVP * vec4(scale * in_vertex, 1.0);"
	// " gl_Position = pos * vec4(scale * in_vertex, 1.0);"
	" gl_Position = MVP * vec4(in_vertex, 1.0);"
	"}";

const GLchar		fragmentSource[] =
	"#version 330 core\n"
	// "in vec2 UV;"
	// "in vec3 fragmentColor;"
	"out vec3 outColor;"
	// "uniform sampler2D myTextureSampler;"
	"void main() {"
	// " outColor = texture( myTextureSampler, UV).rgb;"
	// "	outColor = vec4(fragmentColor, 1.0f);" // R G B Alpha
	"	outColor = vec3(1,0,0);" // R G B Alpha
	"}";

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

	program = glCreateProgram();
	Result = GL_FALSE;

	compile_shader(vertexSource, &program, GL_VERTEX_SHADER);
	compile_shader(fragmentSource, &program, GL_FRAGMENT_SHADER);

	InfoLogLength = 0;
	glGetShaderiv(program, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		glGetProgramInfoLog(program, InfoLogLength, NULL, ProgramErrorMessage);
		printf("ProgramShaderError :\n%s\n", ProgramErrorMessage);
	}
	return program;
}
