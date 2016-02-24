/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:50 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/23 11:33:59 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLMATH_H
# define GLMATH_H

# include <GL/glew.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

struct		s_vec3
{
	GLfloat		data[3];
};
typedef struct s_vec3	t_vec3;

struct		s_vec4
{
	GLfloat		data[4];
};
typedef struct s_vec4	t_vec4;

struct		s_mat4x4
{
	GLfloat		data[4][4];
};
typedef struct s_mat4x4	t_mat4x4;
typedef t_vec4		t_quat;
# define X(x)	x.data[0]
# define Y(x)	x.data[1]
# define Z(x)	x.data[2]
# define W(x)	x.data[3]

# define PX(x)	x->data[0]
# define PY(x)	x->data[1]
# define PZ(x)	x->data[2]
# define PW(x)	x->data[3]

void		normalize(t_vec3 *src);
t_vec3		sub(t_vec3 const a, t_vec3 const b);
t_vec3		cross(t_vec3 const *a, t_vec3 const *b);
GLfloat		dot(t_vec3 const *a, t_vec3 const *b);
void		print_vec3(t_vec3 const *m);

void		compute_normal(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *normal);

t_mat4x4	*new_mat4x4();
void		mul_mat4x4(t_mat4x4 const *a, t_mat4x4 const *b, t_mat4x4 *dest);
void		print_mat(t_mat4x4 const *m);

t_mat4x4	*look_at(t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up);

t_mat4x4	*perspective(GLfloat fov, GLfloat ratio, GLfloat near, GLfloat far);

void		angle_axis(float angle, t_vec3 *axis, t_quat *dest);
float		radians(float degree);

t_quat		quat_mult(t_quat q1, t_quat q2);
void		eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat *dest);
void		quat_to_mat4x4(const t_quat quat, t_mat4x4 *dest);
t_mat4x4	*mat_translation(GLfloat x, GLfloat y, GLfloat z);
t_quat		quat_x_quat(t_quat q1, t_quat q2);

t_vec4		vec3_to_vec4(t_vec3 *src, float w);
t_vec3		vec4_to_vec3(t_vec4 src);
t_vec3		quat_to_vec3(t_vec4 src);

#endif
