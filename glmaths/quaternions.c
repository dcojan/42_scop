/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:01 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:32:49 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void		quat_to_mat4x4(const t_quat quat, t_mat4x4 *dest)
{
	(dest->data)[0][0] = 1 - 2 * ((quat.data[1] * quat.data[1]) +  (quat.data[2] * quat.data[2]));
	(dest->data)[0][1] = 2 * ((quat.data[0] * quat.data[1]) + (quat.data[3] * quat.data[2]));
	(dest->data)[0][2] = 2 * ((quat.data[0] * quat.data[2]) - (quat.data[3] * quat.data[1]));

	(dest->data)[1][0] = 2 * ((quat.data[0] * quat.data[1]) - (quat.data[3] * quat.data[2]));
	(dest->data)[1][1] = 1 - 2 * ((quat.data[0] * quat.data[0]) +  (quat.data[2] * quat.data[2]));
	(dest->data)[1][2] = 2 * ((quat.data[1] * quat.data[2]) + (quat.data[0] * quat.data[3]));

	(dest->data)[2][0] = 2 * ((quat.data[0] * quat.data[2]) + (quat.data[1] * quat.data[3]));
	(dest->data)[2][1] = 2 * ((quat.data[1] * quat.data[2]) - (quat.data[0] * quat.data[3]));
	(dest->data)[2][2] = 1 - 2 * ((quat.data[0] * quat.data[0]) +  (quat.data[1] * quat.data[1]));
}

void		angleAxis(float angle, t_vec3 *axis, t_quat *dest)
{
	float	half_angle;

	half_angle = angle / 2.0f;
	X(dest) = X(axis) * (float)sin(half_angle);
	Y(dest) = Y(axis) * (float)sin(half_angle);
	Z(dest) = Z(axis) * (float)sin(half_angle);
	W(dest) = cos(half_angle);
}

float		radians(float degree)
{
	return (degree * M_PI/180);
}

void		quat_mult(t_quat *q1, t_quat *q2, t_quat *q)
{
	t_vec3	q3 = {{X(q2), Y(q2), Z(q2)}};
	t_vec3	quat_vector = {{X(q1), Y(q1), Z(q1)}};
	t_vec3	uv;

	uv = cross(&quat_vector, &q3);
	t_vec3	uuv;
	uuv = cross(&quat_vector, &uv);
	uv.data[0] *= W(q1);
	uv.data[1] *= W(q1);
	uv.data[2] *= W(q1);

	uuv.data[0] += uv.data[0];
	uuv.data[1] += uv.data[1];
	uuv.data[2] += uv.data[2];

	X(q2) += (uuv.data[0] * 2.0f) ;
	Y(q2) += (uuv.data[1] * 2.0f) ;
	Z(q2) += (uuv.data[2] * 2.0f) ;

	X(q) = X(q2);
	Y(q) = Y(q2);
	Z(q) = Z(q2);
	W(q) = W(q2);
}

void	eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat *dest)
{
	t_vec3 c;
	t_vec3 s;

	c.data[0] = cos(x * 0.5f);
	c.data[1] = cos(y * 0.5f);
	c.data[2] = cos(z * 0.5f);
	s.data[0] = sin(x * 0.5f);
	s.data[1] = sin(y * 0.5f);
	s.data[2] = sin(z * 0.5f);
	dest->data[3] = c.data[0] * c.data[1] * c.data[2] + s.data[0] * s.data[1] * s.data[2];
	dest->data[0] = s.data[0] * c.data[1] * c.data[2] - c.data[0] * s.data[1] * s.data[2];
	dest->data[1] = c.data[0] * s.data[1] * c.data[2] + s.data[0] * c.data[1] * s.data[2];
	dest->data[2] = c.data[0] * c.data[1] * s.data[2] - s.data[0] * s.data[1] * c.data[2];
}
