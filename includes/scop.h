/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:48:35 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "base.h"
# include "glsl_loader.h"
# include "mesh_loader.h"
# include "glmath.h"

typedef struct		s_mouse_coord
{
	int				x;
	int				y;
}					t_mouse_coord;

typedef enum		s_event
{
	QUIT,
	OBJ_ROT_Y,
	OBJ_ROT_Y_REV,
	OBJ_ROT_X,
	OBJ_ROT_X_REV,
	OBJ_ROT_Z,
	OBJ_ROT_Z_REV,
	OBJ_ROT_RESET,
	START_CAMERA_MOVE,
	STOP_CAMERA_MOVE,
	CAMERA_MOVE,
	NO_EVENT,
	TOTAL_EVENT,
}					t_event;

typedef struct		s_keyevent
{
	uint32_t		type;
	SDL_Keycode		code;
	t_event			event;
}					t_keyevent;

/*
** scop.c
*/

void		scop(t_mesh *mesh, t_sdl *sdl_var);

/*
** main_loop.c
*/

void 		main_loop(t_sdl	*sdl_var, t_mesh *mesh);

t_event		get_scop_event();

void		rotate_model(GLuint program, int axis, t_bool reverse, t_bool reset);

void		handle_event(t_event event, GLuint program);

/*
** buffers.c
*/

GLuint  	new_buffer(GLuint type, GLuint size, GLfloat *vertices, GLuint draw);

/*
** shaders.c
*/

GLuint		load_shaders();

void		setup_mesh(t_mesh *mesh);

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
