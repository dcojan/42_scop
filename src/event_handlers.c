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
	(void)event;
	auto_rotation(mesh);
}

void		event_translation(t_event event, t_mesh *mesh)
{
	if (event == OBJ_TRANS_X_REV)
		translate_model(mesh, 0, TRUE, FALSE);
	else if (event == OBJ_TRANS_X)
		translate_model(mesh, 0, FALSE, FALSE);
	else if (event == OBJ_TRANS_Y_REV)
		translate_model(mesh, 1, TRUE, FALSE);
	else if (event == OBJ_TRANS_Y)
		translate_model(mesh, 1, FALSE, FALSE);
	else if (event == OBJ_TRANS_Z_REV)
		translate_model(mesh, 2, TRUE, FALSE);
	else if (event == OBJ_TRANS_Z)
		translate_model(mesh, 2, FALSE, FALSE);
	else if (event == OBJ_TRANS_RESET)
		translate_model(mesh, -1, FALSE, TRUE);

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
	&event_translation,
	&event_translation,
	&event_translation,
	&event_translation,
	&event_translation,
	&event_translation,
	&event_translation,
	&event_camera,
	&event_camera,
	&event_camera,
	&event_empty,
};

void		handle_event(t_event event, t_mesh *mesh)
{
	(*g_f[event])(event, mesh);
}
