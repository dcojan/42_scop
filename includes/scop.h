/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/23 11:47:49 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "base.h"
# include "glsl_loader.h"
# include "bmp_loader.h"
# include "mesh_loader.h"
# include "glmath.h"

struct	s_mouse_coord
{
	int				x;
	int				y;
};
typedef struct s_mouse_coord	t_mouse_coord;

enum	e_event
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
};
typedef enum e_event			t_event;

struct	s_keyevent
{
	uint32_t		type;
	SDL_Keycode		code;
	t_event			event;
};
typedef struct s_keyevent		t_keyevent;

/*
** scop.c
*/

void	scop(t_mesh *mesh, t_sdl *sdl_var);

/*
** main_loop.c
*/

void	main_loop(t_sdl	*sdl_var, t_mesh *mesh);
t_event	get_scop_event();
void	rotate_model(t_mesh *mesh, int axis, t_bool reverse, t_bool reset);
void	handle_event(t_event event, t_mesh *mesh);

/*
** buffers.c
*/

GLuint	new_buffer(GLuint type, GLuint size, GLfloat *vertices, GLuint draw);
GLuint	new_texture_buffer(uint width, uint height, uint8_t *data);

/*
** shaders.c
*/
uint	load_shaders();
void	setup_mesh(t_mesh *mesh);

/*
** camera.c
*/

void	set_camera(GLfloat x, GLfloat y, GLfloat z, GLuint program);
void	move_camera(int x, int y, GLuint progid, float speed);

/*
** light.c
*/

void	set_light(GLfloat x, GLfloat y, GLfloat z, GLuint program);

#endif
