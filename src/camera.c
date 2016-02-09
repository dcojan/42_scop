#include <scop.h>

void		set_camera(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLuint shaderProgram)
{
	t_mat4x4 *ProjectionMatrix = perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	t_vec3 eye = {eyeX,eyeY,eyeZ};
	t_vec3 center = {0,0,0};
	t_vec3 up = {0,1,0};
	t_mat4x4 * ViewMatrix = lookAt(&eye, &center, &up);
	t_mat4x4 mvp;
    mul_mat4x4(ViewMatrix, ProjectionMatrix, &mvp);
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(shaderProgram, "V");
	GLuint ModelMatrixID = glGetUniformLocation(shaderProgram, "M");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(mvp)[0][0]);
	t_mat4x4 ModelMatrix;
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &((*ViewMatrix)[0][0]));
    // print_mat(ProjectionMatrix);
	// print_mat(ViewMatrix);
	// print_mat(&mvp);
}
