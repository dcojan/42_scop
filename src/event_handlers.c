/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:46:24 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:19:15 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		event_empty(t_event event, t_mesh *mesh)
{
	(void)event;
	(void)mesh;
}

void		event_rotation(t_event event, t_mesh *mesh)
{
	if (event == OBJ_ROT_X_REV)
		rotate_model(mesh, 0, TRUE, FALSE);
	else if (event == OBJ_ROT_X)
		rotate_model(mesh, 0, FALSE, FALSE);
	else if (event == OBJ_ROT_Y_REV)
		rotate_model(mesh, 1, TRUE, FALSE);
	else if (event == OBJ_ROT_Y)
		rotate_model(mesh, 1, FALSE, FALSE);
	else if (event == OBJ_ROT_Z_REV)
		rotate_model(mesh, 2, TRUE, FALSE);
	else if (event == OBJ_ROT_Z)
		rotate_model(mesh, 2, FALSE, FALSE);
	else if (event == OBJ_ROT_RESET)
		rotate_model(mesh, 0, FALSE, TRUE);
}

void		event_camera(t_event event, t_mesh *mesh)
{
	static t_mouse_coord		mousebase = {0, 0};
	t_mouse_coord				mouse;

	if (event == START_CAMERA_MOVE)
	{
		SDL_GetMouseState(&(mousebase.x), &(mousebase.y));
		mouse.x = mousebase.x;
		mouse.y = mousebase.y;
	}
	else if (event == CAMERA_MOVE)
	{
		SDL_GetMouseState(&(mouse.x), &(mouse.y));
		move_camera(mouse.x - mousebase.x, mouse.y - mousebase.y,
			mesh->shader_program, 3.0f);
		mousebase.x = mouse.x;
		mousebase.y = mouse.y;
	}
}

static void		(*const g_f[TOTAL_EVENT])(t_event, t_mesh *) =
{
	&event_empty,
	&event_rotation,
	&event_rotation,
	&event_rotation,
	&event_rotation,
	&event_rotation,
	&event_rotation,
	&event_rotation,
	&event_camera,
	&event_camera,
	&event_camera,
	&event_empty,
};

void		handle_event(t_event event, t_mesh *mesh)
{
	(*g_f[event])(event, mesh);
}
