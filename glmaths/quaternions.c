/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:01 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:17:01 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

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
	t_vec3	q3 = {X(q2), Y(q2), Z(q2)};
	t_vec3	quat_vector = {X(q1), Y(q1), Z(q1)};
	t_vec3	uv;
	cross(&quat_vector, &q3, &uv);
	t_vec3	uuv;
	cross(&quat_vector, &uv, &uuv);
	uv[0] *= W(q1);
	uv[1] *= W(q1);
	uv[2] *= W(q1);

	uuv[0] += uv[0];
	uuv[1] += uv[1];
	uuv[2] += uv[2];

	X(q2) += (uuv[0] * 2.0f) ;
	Y(q2) += (uuv[1] * 2.0f) ;
	Z(q2) += (uuv[2] * 2.0f) ;

	X(q) = X(q2);
	Y(q) = Y(q2);
	Z(q) = Z(q2);
	W(q) = W(q2);
}

void	eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat dest)
{
	t_vec3 c;
	t_vec3 s;

	c[0] = cos(x * 0.5f);
	c[1] = cos(y * 0.5f);
	c[2] = cos(z * 0.5f);
	s[0] = sin(x * 0.5f);
	s[1] = sin(y * 0.5f);
	s[2] = sin(z * 0.5f);
	dest[3] = c[0] * c[1] * c[2] + s[0] * s[1] * s[2];
	dest[0] = s[0] * c[1] * c[2] - c[0] * s[1] * s[2];
	dest[1] = c[0] * s[1] * c[2] + s[0] * c[1] * s[2];
	dest[2] = c[0] * c[1] * s[2] - s[0] * s[1] * c[2];
}
