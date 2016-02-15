/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:50 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:34:15 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLMATH_H
# define GLMATH_H

#include <GL/glew.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// typedef GLfloat   t_vec3[3];
// typedef GLfloat   t_vec4[4];
// typedef GLfloat   t_mat4x4[4][4];
// typedef GLfloat   t_quat[4];

typedef struct		s_vec3
{
	GLfloat   data[3];
}					t_vec3;


typedef struct		s_vec4
{
	GLfloat   data[4];
}					t_vec4;


typedef struct		s_mat4x4
{
	GLfloat   data[4][4];
}					t_mat4x4;


typedef struct		s_quat
{
	GLfloat   data[4];
}					t_quat;
//
// #define X(x)    (*x)[0]
// #define Y(x)    (*x)[1]
// #define Z(x)    (*x)[2]
// #define W(x)    (*x)[3]


#define X(x)    (x->data)[0]
#define Y(x)    (x->data)[1]
#define Z(x)    (x->data)[2]
#define W(x)    (x->data)[3]
// vec3
void        normalize(t_vec3 *src);
t_vec3		sub(t_vec3 const a, t_vec3 const b);
t_vec3      cross(t_vec3 const *a, t_vec3 const *b);
GLfloat     dot(t_vec3 const *a, t_vec3 const *b);
void        print_vec3(t_vec3 const *m);

void		compute_normal(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *normal);

// mat4x4
t_mat4x4    *new_mat4x4();
void        mul_mat4x4(t_mat4x4 const *a, t_mat4x4 const *b, t_mat4x4 *dest);
void        print_mat(t_mat4x4 const *m);

// lookat
t_mat4x4    *lookAt(t_vec3 const *eye, t_vec3  const *center, t_vec3  const *up);

// perspective
t_mat4x4	*perspective(GLfloat fovy, GLfloat ratio, GLfloat near, GLfloat far);

void		angleAxis(float angle, t_vec3 *axis, t_quat *dest);
float		radians(float degree);

void		quat_mult(t_quat *q1, t_quat *q2, t_quat *q);
void		eul_to_quat(GLfloat x, GLfloat y, GLfloat z, t_quat *dest);
void		quat_to_mat4x4(const t_quat quat, t_mat4x4 *dest);

t_vec4		vec3_to_vec4(t_vec3 *src, float w);

#endif
