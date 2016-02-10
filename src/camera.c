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

	projection = perspective(radians(45.0f),
		(GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	printf("PROJECTION\n");
	for (int i = 0; i < 4; i++)
	 	printf("%f %f %f %f\n", (*projection)[i][0], (*projection)[i][1], (*projection)[i][2], (*projection)[i][3]);
	view = view_matrix(eyex, eyey, eyez);
	printf("VIEW\n");
	for (int i = 0; i < 4; i++)
	 	printf("%f %f %f %f\n", (*view)[i][0], (*view)[i][1], (*view)[i][2], (*view)[i][3]);

	proj_unif_id = glGetUniformLocation(progid, "Projection");
	view_unif_id = glGetUniformLocation(progid, "View");
	glUniformMatrix4fv(proj_unif_id, 1, GL_FALSE, &((*projection)[0][0]));
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((*view)[0][0]));
}

void		move_camera(int x, int y, GLuint prog)
{
	float speed = 1.0f;
	t_vec3 position = {4.0f, 3.0f, 5.0f};
	float yawAngle = 1.0f * speed;
 	float pitchAngle = 1.0f * speed;

	t_vec3 target = {0.f, 0.f, 0.f};
	t_vec3 camera_up_vector = {0.f, 1.f, 0.f};
	t_vec3 target_to_camera_vector;
	t_vec3 camera_right_vector;

	sub(&position, &target, &target_to_camera_vector);
	cross(&target_to_camera_vector, &camera_up_vector, &camera_right_vector);
	normalize(&camera_right_vector);

	pitchAngle *= y / 20.0f;
	t_quat	pitch;
	angleAxis(radians(pitchAngle), &camera_right_vector, &pitch);
	t_vec4	tmp;
	vec3_to_vec4(&position, 1.0f, &tmp);
	t_vec4	tmp2;
	quat_mult((t_quat*)&pitch, &tmp, &tmp2);
	// position = glm::vec3(pitch * tmp);
	position[0] = tmp2[0];
	position[1] = tmp2[1];
	position[2] = tmp2[2];

	yawAngle *= -x / 20.0f;
	t_quat yaw;
	yaw[0] = radians(0.0f);
	yaw[1] = radians(yawAngle);
	yaw[2] = radians(0.0f);
	yaw[3] = 0.0f;
	// t_quat yaw = glm::quat(glm::radians(glm::vec3(0.0f, yawAngle, 0.0f)));
	vec3_to_vec4(&position, 1.0f, &tmp);

	quat_mult((t_quat*)&yaw, &tmp, &tmp2);
	// position = glm::vec3(yaw * glm::vec4(position, 1.0f));
	position[0] = tmp2[0];
	position[1] = tmp2[1];
	position[2] = tmp2[2];
	// ViewMatrix = lookAt(&position, &target, &camera_up_vector);

	t_mat4x4		*view;
	GLuint			view_unif_id;
	view = view_matrix(position[0], position[1], position[2]);
	view_unif_id = glGetUniformLocation(prog, "View");
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((*view)[0][0]));

}
