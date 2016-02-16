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
	(dest->data)[0][0] = 1 - 2 * ((Y(quat) * Y(quat)) +  (Z(quat) * Z(quat)));
	(dest->data)[0][1] = 2 * ((X(quat) * Y(quat)) + (W(quat) * Z(quat)));
	(dest->data)[0][2] = 2 * ((X(quat) * Z(quat)) - (W(quat) * Y(quat)));

	(dest->data)[1][0] = 2 * ((X(quat) * Y(quat)) - (W(quat) * Z(quat)));
	(dest->data)[1][1] = 1 - 2 * ((X(quat) * X(quat)) +  (Z(quat) * Z(quat)));
	(dest->data)[1][2] = 2 * ((Y(quat) * Z(quat)) + (X(quat) * W(quat)));

	(dest->data)[2][0] = 2 * ((X(quat) * Z(quat)) + (Y(quat) * W(quat)));
	(dest->data)[2][1] = 2 * ((Y(quat) * Z(quat)) - (X(quat) * W(quat)));
	(dest->data)[2][2] = 1 - 2 * ((X(quat) * X(quat)) +  (Y(quat) * Y(quat)));
}

void		angleAxis(float angle, t_vec3 *axis, t_quat *dest)
{
	float	half_angle;

	half_angle = angle / 2.0f;
	PX(dest) = PX(axis) * (float)sin(half_angle);
	PY(dest) = PY(axis) * (float)sin(half_angle);
	PZ(dest) = PZ(axis) * (float)sin(half_angle);
	PW(dest) = cos(half_angle);
}

float		radians(float degree)
{
	return (degree * M_PI/180);
}

t_quat		quat_mult(t_quat q1, t_quat q2)
{
	t_quat	dest;
	t_vec3	q3 = {{q2.data[0], q2.data[1], q2.data[2]}};
	t_vec3	quat_vector = {{q1.data[0], q1.data[1], q1.data[2]}};
	t_vec3	uv;

	uv = cross(&quat_vector, &q3);
	t_vec3	uuv;
	uuv = cross(&quat_vector, &uv);
	uv.data[0] *= q1.data[3];
	uv.data[1] *= q1.data[3];
	uv.data[2] *= q1.data[3];

	uuv.data[0] += uv.data[0];
	uuv.data[1] += uv.data[1];
	uuv.data[2] += uv.data[2];

	q2.data[0] += (uuv.data[0] * 2.0f) ;
	q2.data[1] += (uuv.data[1] * 2.0f) ;
	q2.data[2] += (uuv.data[2] * 2.0f) ;

	dest.data[0] = q2.data[0];
	dest.data[1] = q2.data[1];
	dest.data[2] = q2.data[2];
	dest.data[3] = q2.data[3];
	return (dest);
}

void	eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat *dest)
{
	t_vec3 c;
	t_vec3 s;

	X(c) = cos(x * 0.5f);
	Y(c) = cos(y * 0.5f);
	Z(c) = cos(z * 0.5f);
	X(s) = sin(x * 0.5f);
	Y(s) = sin(y * 0.5f);
	Z(s) = sin(z * 0.5f);
	dest->data[3] = X(c) * Y(c) * Z(c) + X(s) * Y(s) * Z(s);
	dest->data[0] = X(s) * Y(c) * Z(c) - X(c) * Y(s) * Z(s);
	dest->data[1] = X(c) * Y(s) * Z(c) + X(s) * Y(c) * Z(s);
	dest->data[2] = X(c) * Y(c) * Z(s) - X(s) * Y(s) * Z(c);
}
