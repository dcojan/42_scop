/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 17:13:53 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "base.h"
# include "glsl_loader.h"
# include "object_loader.h"
# include "glmath.h"

typedef enum		s_event
{
	NO_EVENT,
	QUIT,
	START_CAMERA_MOVE,
	CAMERA_MOVE,
	STOP_CAMERA_MOVE,
	OBJ_ROT_X,
	OBJ_ROT_X_REV,
	OBJ_ROT_Y,
	OBJ_ROT_Y_REV,
	OBJ_ROT_Z,
	OBJ_ROT_Z_REV,
	TOTAL_EVENT,
}					t_event;

/*
** scop.c
*/

void		scop(t_obj *obj, t_sdl *sdl_var);

/*
** main_loop.c
*/

void 		main_loop(t_sdl	*sdl_var,GLuint shaderProgram, t_obj *obj);

/*
** buffers.c
*/

GLuint  	new_buffer(GLuint type, GLuint size, GLfloat *vertices, GLuint draw);

/*
** shaders.c
*/

GLuint		load_shaders();

/*
** camera.c
*/

void		set_camera(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLuint shaderProgram);
void		move_camera(int x, int y, GLuint progid, float speed);

/*
** light.c
*/

void		set_light(GLfloat lightX, GLfloat lightY, GLfloat lightZ, GLuint shaderProgram);


#endif
