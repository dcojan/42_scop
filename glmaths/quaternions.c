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
	X(q) = (W(q1) * X(q2)) + (X(q1) * W(q2)) + (Y(q1) * Z(q2)) - (Z(q1) * Y(q2));
	Y(q) = (W(q1) * Y(q2)) - (X(q1) * Z(q2)) + (Y(q1) * W(q2)) + (Z(q1) * X(q2));
	Z(q) = (W(q1) * Z(q2)) + (X(q1) * Y(q2)) - (Y(q1) * X(q2)) + (Z(q1) * W(q2));
	W(q) = (W(q1) * W(q2)) - (X(q1) * X(q2)) - (Y(q1) * Y(q2)) - (Z(q1) * Z(q2));
}
