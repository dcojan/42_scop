/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:01 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 11:23:58 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void		quat_to_mat4x4(const t_quat quat, t_mat4x4 *dest)
{
	(dest->data)[0][0] = 1 - 2 * ((Y(quat) * Y(quat)) + (Z(quat) * Z(quat)));
	(dest->data)[0][1] = 2 * ((X(quat) * Y(quat)) + (W(quat) * Z(quat)));
	(dest->data)[0][2] = 2 * ((X(quat) * Z(quat)) - (W(quat) * Y(quat)));
	(dest->data)[1][0] = 2 * ((X(quat) * Y(quat)) - (W(quat) * Z(quat)));
	(dest->data)[1][1] = 1 - 2 * ((X(quat) * X(quat)) + (Z(quat) * Z(quat)));
	(dest->data)[1][2] = 2 * ((Y(quat) * Z(quat)) + (X(quat) * W(quat)));
	(dest->data)[2][0] = 2 * ((X(quat) * Z(quat)) + (Y(quat) * W(quat)));
	(dest->data)[2][1] = 2 * ((Y(quat) * Z(quat)) - (X(quat) * W(quat)));
	(dest->data)[2][2] = 1 - 2 * ((X(quat) * X(quat)) + (Y(quat) * Y(quat)));
}

void		angle_axis(float angle, t_vec3 *axis, t_quat *dest)
{
	float	half_angle;

	half_angle = angle / 2.0f;
	PX(dest) = PX(axis) * (float)sin(half_angle);
	PY(dest) = PY(axis) * (float)sin(half_angle);
	PZ(dest) = PZ(axis) * (float)sin(half_angle);
	PW(dest) = cos(half_angle);
}

t_quat		quat_mult(t_quat q1, t_quat q2)
{
	t_quat	dest;
	t_vec3	uuv;
	t_vec3	uv;
	t_vec3	q3;
	t_vec3	quat_vector;

	q3 = quat_to_vec3(q2);
	quat_vector = quat_to_vec3(q1);
	uv = cross(&quat_vector, &q3);
	uuv = cross(&quat_vector, &uv);
	uv.data[0] *= q1.data[3];
	uv.data[1] *= q1.data[3];
	uv.data[2] *= q1.data[3];
	uuv.data[0] += uv.data[0];
	uuv.data[1] += uv.data[1];
	uuv.data[2] += uv.data[2];
	q2.data[0] += (uuv.data[0] * 2.0f);
	q2.data[1] += (uuv.data[1] * 2.0f);
	q2.data[2] += (uuv.data[2] * 2.0f);
	dest.data[0] = q2.data[0];
	dest.data[1] = q2.data[1];
	dest.data[2] = q2.data[2];
	dest.data[3] = q2.data[3];
	return (dest);
}

t_quat		quat_x_quat(t_quat q1, t_quat q2)
{
	t_quat	q;

	X(q) = (W(q1) * X(q2)) + (X(q1) * W(q2));
	X(q) += (Y(q1) * Z(q2)) - (Z(q1) * Y(q2));
	Y(q) = (W(q1) * Y(q2)) - (X(q1) * Z(q2));
	Y(q) += (Y(q1) * W(q2)) + (Z(q1) * X(q2));
	Z(q) = (W(q1) * Z(q2)) + (X(q1) * Y(q2));
	Z(q) -= (Y(q1) * X(q2)) + (Z(q1) * W(q2));
	W(q) = (W(q1) * W(q2)) - (X(q1) * X(q2));
	W(q) -= (Y(q1) * Y(q2)) - (Z(q1) * Z(q2));
	return (q);
}

void		eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat *dest)
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
