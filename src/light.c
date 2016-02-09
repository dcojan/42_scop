#include <scop.h>

void		set_light(GLfloat lightX, GLfloat lightY, GLfloat lightZ, GLuint shaderProgram)
{
	GLuint LightID = glGetUniformLocation(shaderProgram, "light_position_worldspace");
	glUniform3f(LightID, lightX, lightY, lightZ);
}
