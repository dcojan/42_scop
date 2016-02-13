/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:11:25 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 17:01:21 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// printf("SET CAMERA\n");
	projection = perspective(radians(45.0f),
		(GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	// printf("PROJECTION\n");
	// for (int i = 0; i < 4; i++)
	//  	printf("%f %f %f %f\n", (*projection)[i][0], (*projection)[i][1], (*projection)[i][2], (*projection)[i][3]);
	view = view_matrix(eyex, eyey, eyez);
	// printf("VIEW\n");
	// for (int i = 0; i < 4; i++)
	//  	printf("%f %f %f %f\n", (*view)[i][0], (*view)[i][1], (*view)[i][2], (*view)[i][3]);

	proj_unif_id = glGetUniformLocation(progid, "Projection");
	view_unif_id = glGetUniformLocation(progid, "View");
	glUniformMatrix4fv(proj_unif_id, 1, GL_FALSE, &((*projection)[0][0]));
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((*view)[0][0]));
	// printf("done.\n");
}

void		move_position_pitch(float pitch_angle, t_vec3 *position, int y)
{
	static const t_vec3 target = {0.0f, 0.0f, 0.0f};
	static const t_vec3 camera_up_vector = {0.f, 1.f, 0.f};
	t_vec3 target_to_camera_vector;
	t_vec3 camera_right_vector;

	sub(*position, target, target_to_camera_vector);
	cross(&target_to_camera_vector, &camera_up_vector, &camera_right_vector);
	normalize(&camera_right_vector);
	// printf("'\nCamera right vector\n");
	// printf("%f %f %f\n", camera_right_vector[0], camera_right_vector[1], camera_right_vector[2]);

	pitch_angle *= y / 20.0f;
	t_quat	pitch;
	angleAxis(radians(pitch_angle), &camera_right_vector, &pitch);
	// printf("pitch\n");
	// printf("%f %f %f %f\n", pitch[0], pitch[1], pitch[2], pitch[3]);

	t_vec4	tmp;
	vec3_to_vec4(position, 1.0f, &tmp);
	// printf("to vec\n");
	// printf("%f %f %f %f\n", tmp[0], tmp[1], tmp[2], tmp[3]);

	t_vec4	tmp2;
	quat_mult(&pitch, &tmp, &tmp2);
	// printf("quat mul\n");
	// printf("%f %f %f %f\n", tmp2[0], tmp2[1], tmp2[2], tmp2[3]);

	X(position) = tmp2[0];
	Y(position) = tmp2[1];
	Z(position) = tmp2[2];
}

void		move_position_yaw(float yaw_angle, t_vec3 *position, int x)
{
	t_quat		yaw;
	t_vec4		tmp;
	t_vec4		tmp2;

	yaw_angle *= -x / 20.0f;
	eul_to_quat(radians(0.0f), radians(yaw_angle), radians(0.0f), yaw);
	// printf("yaw\n");
	// printf("%f %f %f %f\n", yaw[0], yaw[1], yaw[2], yaw[3]);
	vec3_to_vec4(position, 1.0f, &tmp);
	// printf("tmp\n");
	// printf("%f %f %f %f\n", tmp[0], tmp[1], tmp[2], tmp[3]);
	quat_mult((t_quat*)&yaw, &tmp, &tmp2);
	// quat_mult(&tmp, &yaw, &tmp2);
	// printf("quat mul\n");
	// printf("%f %f %f %f\n", tmp2[0], tmp2[1], tmp2[2], tmp2[3]);

	X(position) = tmp2[0];
	Y(position) = tmp2[1];
	Z(position) = tmp2[2];
}

// #include <unistd.h> // sleep
void		move_camera(int x, int y, GLuint prog, float speed)
{
	static t_vec3		position = {0.0f, 0.0f, 5.0f};
	float				yaw_angle;
 	float				pitch_angle;
	t_mat4x4			*view;
	GLuint				view_unif_id;

	yaw_angle = 1.0f * speed;
	pitch_angle = 1.0f * speed;
	// x = 1;
	// y = 0;
	// sleep(1);

	move_position_pitch(pitch_angle, &position, y);
	// printf("position1\n");
	// printf("%f %f %f\n", position[0], position[1], position[2]);
	move_position_yaw(yaw_angle, &position, x);

	// printf("position2\n");
	// printf("%f %f %f\n", position[0], position[1], position[2]);

	view = view_matrix(position[0], position[1], position[2]);
	view_unif_id = glGetUniformLocation(prog, "View");
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((*view)[0][0]));
}
