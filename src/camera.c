/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:11:25 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/15 17:52:22 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_mat4x4	*view_matrix(GLfloat eyex, GLfloat eyey, GLfloat eyez)
{
	t_mat4x4		*view_m;
	t_vec3 const	eye = {{eyex, eyey, eyez}};
	t_vec3 const	center = {{0, 0, 0}};
	t_vec3 const	up = {{0, 1, 0}};

	view_m = look_at(&eye, &center, &up);
	return (view_m);
}

void		set_projection(float zoom_factor, GLuint progid)
{
	t_mat4x4		*projection;
	GLuint			proj_unif_id;

	projection = perspective(radians(45.0f * zoom_factor),
		(GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	proj_unif_id = glGetUniformLocation(progid, "Projection");
	glUniformMatrix4fv(proj_unif_id, 1, GL_FALSE, &((projection->data)[0][0]));
}

void		set_camera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLuint progid)
{
	GLuint			view_unif_id;
	t_mat4x4		*view;

	set_projection(1.0f, progid);
	view = view_matrix(eyex, eyey, eyez);
	view_unif_id = glGetUniformLocation(progid, "View");
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((view->data)[0][0]));
}

void		move_position_pitch(float pitch_angle, t_vec3 *position, int y)
{
	static const t_vec3		target = {{0.0f, 0.0f, 0.0f}};
	static const t_vec3		camera_up_vector = {{0.f, 1.f, 0.f}};
	t_vec3					target_to_camera_vector;
	t_vec3					camera_right_vector;
	t_quat					pitch;

	target_to_camera_vector = sub(*position, target);
	camera_right_vector = cross(&target_to_camera_vector, &camera_up_vector);
	normalize(&camera_right_vector);
	pitch_angle *= y / 20.0f;
	angle_axis(radians(pitch_angle), &camera_right_vector, &pitch);
	*position = vec4_to_vec3(quat_mult(pitch, vec3_to_vec4(position, 1.0f)));
}

void		move_position_yaw(float yaw_angle, t_vec3 *position, int x)
{
	t_quat		yaw;

	yaw_angle *= -x / 20.0f;
	eul_to_quat(radians(0.0f), radians(yaw_angle), radians(0.0f), &yaw);
	*position = vec4_to_vec3(quat_mult(yaw, vec3_to_vec4(position, 1.0f)));
}

void		move_camera(int x, int y, GLuint prog, float speed)
{
	static t_vec3		position = {{CAM_X, CAM_Y, CAM_Z}};
	float				yaw_angle;
	float				pitch_angle;
	t_mat4x4			*view;
	GLuint				view_unif_id;

	yaw_angle = 1.0f * speed;
	pitch_angle = 1.0f * speed;
	move_position_pitch(pitch_angle, &position, y);
	move_position_yaw(yaw_angle, &position, x);
	view = view_matrix(position.data[0], position.data[1], position.data[2]);
	view_unif_id = glGetUniformLocation(prog, "View");
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((view->data)[0][0]));
}
