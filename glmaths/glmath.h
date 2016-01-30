#ifndef GLMATH_H
# define GLMATH_H

#include <GL/glew.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef GLfloat   t_vec3[3];
typedef GLfloat   t_vec4[4];
typedef GLfloat   t_mat4x4[4][4];

#define X(x)    (*x)[0]
#define Y(x)    (*x)[1]
#define Z(x)    (*x)[2]

t_mat4x4    *lookAt(t_vec3 const *eye, t_vec3  const *center, t_vec3  const *up);
t_mat4x4    *new_mat4x4();
void        mul_mat4x4(t_mat4x4 const *a, t_mat4x4 const *b, t_mat4x4 *dest);
void        print_mat(t_mat4x4 const *m);

#endif
