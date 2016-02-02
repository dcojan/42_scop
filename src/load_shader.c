#include <scop.h>

const GLchar		vertexSource[] =
	"#version 330 core\n"
	"layout(location = 0) in vec3 in_vertex;"
	"layout(location = 2) in vec3 in_normal;"
    // "layout(location = 1) in vec3 vertexColor;"
	// "vec3 vertexColor = vec3(1.0f,0.0f,0.0f);"
	// "layout(location = 1) in vec2 vertexUV;"

	// "out vec3 fragmentColor;"
	// "out vec2 UV;"
	"out vec3 position_world_space;"
	"out vec3 normal_camera_space;"
	"out vec3 light_direction_camera_space;"
	"out vec3 eye_direction_camera_space;"

	"uniform mat4 MVP;"
	"uniform mat4 V;"
	// "uniform mat4 M;"
	"uniform vec3 light_position_worldspace;"

	"smooth out vec3 vNormal;"

	"void main() {"
	" gl_Position = MVP * vec4(in_vertex, 1.0);"
	// " position_world_space = (M * vec4(in_vertex, 1.0)).xyz;"
	" position_world_space = ( vec4(in_vertex, 1.0)).xyz;"

	// " vec3 vertex_position_cameraspace = (V * M * vec4(in_vertex, 1.0)).xyz;"
	" vec3 vertex_position_cameraspace = (V * vec4(in_vertex, 1.0)).xyz;"
	" eye_direction_camera_space = vec3(0,0,0) - vertex_position_cameraspace;"
	//
	" vec3 light_position_cameraspace = (V * vec4(light_position_worldspace, 1.0)).xyz;"
	" light_direction_camera_space = light_position_cameraspace + eye_direction_camera_space;"

	"normal_camera_space = (V * vec4(in_normal, 0)).xyz;"
	// "normal_camera_space = (V * M * vec4(in_normal, 0)).xyz;"
	// "	fragmentColor = vertexColor;"
	// "UV = vertexUV;"
	"}";

// const GLchar		fragmentSource[] =
// "#version 330\n"
//
// // "in vec2 texCoord;"
// "smooth in vec3 vNormal;"
// "out vec4 outputColor;"
//
// "uniform sampler2D gSampler;"
// "uniform vec4 vColor;"
//
// "struct SimpleDirectionalLight"
// "{"
//   " vec3 vColor;"
//    "vec3 vDirection;"
//    "float fAmbientIntensity;"
// "};"
//
// "uniform SimpleDirectionalLight sunLight;"
//
// "void main()"
// "{"
// // " vec4 vTexColor = texture2D(gSampler, texCoord);"
//   " float fDiffuseIntensity = max(0.0, dot(normalize(vNormal), -sunLight.vDirection));"
//   // " outputColor = vTexColor*vColor*vec4(sunLight.vColor*(sunLight.fAmbientIntensity+fDiffuseIntensity), 1.0);"
//   " outputColor = vColor*vec4(sunLight.vColor*(sunLight.fAmbientIntensity+fDiffuseIntensity), 1.0);"
// "}";

const GLchar		fragmentSource[] =
	"#version 330 core\n"
	"in vec3 position_world_space;"
	"in vec3 normal_camera_space;"
	"in vec3 eye_direction_camera_space;"
	"in vec3 light_direction_camera_space;"
	// "in vec2 UV;"
	// "in vec3 fragmentColor;"
	"out vec3 outColor;"
	// "uniform sampler2D myTextureSampler;"

	"uniform vec3 light_position_worldspace;"

	"void main() {"
	// " outColor = texture( myTextureSampler, UV).rgb;"
	// "	outColor = vec4(fragmentColor, 1.0f);" // R G B Alpha
	// Light emission properties
	// You probably want to put them as uniforms
	"vec3 LightColor = vec3(1,1,1);"
	"float LightPower = 50.0f;"

	// Material properties
	// "vec3 MaterialDiffuseColor = texture( myTextureSampler, UV ).rgb;"
	"vec3 MaterialDiffuseColor = vec3(0.0, 1.0, 0.0);"
	"vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;"
	"vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);"

	// Distance to the light
	"float distance = length( light_position_worldspace - position_world_space );"

	// Normal of the computed fragment, in camera space
	"vec3 n = normalize( normal_camera_space );"

	// Direction of the light (from the fragment to the light)
	"vec3 l = normalize( light_direction_camera_space );"

	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	"float cosTheta = clamp( dot( n,l ), 0,1 );"

	// Eye vector (towards the camera)
	"vec3 E = normalize(eye_direction_camera_space);"
	// Direction in which the triangle reflects the light
	"vec3 R = reflect(-l,n);"
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	"float cosAlpha = clamp( dot( E,R ), 0,1 );"

	"outColor ="
		// Ambient : simulates indirect lighting
		"MaterialAmbientColor +"
		// Diffuse : "color" of the object
		"MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +"
		// Specular : reflective highlight, like a mirror
		"MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);"

	// "	outColor = vec3(1,0,0);" // R G B Alpha
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
