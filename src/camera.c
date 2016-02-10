#include <scop.h>

t_mat4x4	*view_matrix(GLfloat eyex, GLfloat eyey, GLfloat eyez)
{
	t_mat4x4		*view_m;
	t_vec3 const	eye = {eyex, eyey, eyez};
	t_vec3 const	center = {0, 0, 0};
	t_vec3 const	up = {0, 1, 0};

	view_m = lookAt(&eye, &center, &up);
	return (view_m);
}

void		set_camera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLuint progid)
{
	GLuint			proj_unif_id;
	GLuint			view_unif_id;
	t_mat4x4		*projection;
	t_mat4x4		*view;

	projection = perspective(45.0f,
		(GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	view = view_matrix(eyex, eyey, eyez);
	proj_unif_id = glGetUniformLocation(progid, "Projection");
	view_unif_id = glGetUniformLocation(progid, "View");
	glUniformMatrix4fv(proj_unif_id, 1, GL_FALSE, &((*projection)[0][0]));
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((*view)[0][0]));
}
