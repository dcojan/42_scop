#include <scop.h>

void		set_light(GLfloat x, GLfloat y, GLfloat z, GLuint program)
{
	GLuint light_id;

	light_id = glGetUniformLocation(program, "light_position_worldspace");
	glUniform3f(light_id, x, y, z);
}
