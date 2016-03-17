/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:46:24 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 11:43:37 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		event_translation(t_event event, t_mesh *mesh, void *arg)
{
	(void)arg;
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

void		event_camera(t_event event, t_mesh *mesh, void *arg)
{
	static t_mouse_coord		mousebase = {0, 0};
	t_mouse_coord				mouse;

	(void)arg;
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

void		event_light(t_event event, t_mesh *mesh, void *arg)
{
	static GLfloat		light_power = LIGHT_POWER;
	int					id;

	(void)arg;
	id = glGetUniformLocation(mesh->shader_program, "LightPower");
	if (event == LIGHT_MORE && light_power < 200)
		light_power += 10;
	else if (event == LIGHT_LESS && light_power > 0)
		light_power -= 10;
	glUniform1fv(id, 1, &light_power);
}

static void		(*const g_f[TOTAL_EVENT])(t_event, t_mesh *, void *) =
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
	&event_light,
	&event_light,
	&event_zoom,
	&event_zoom,
	&event_texture,
	&event_camera,
	&event_camera,
	&event_camera,
	&event_empty,
};

void		handle_event(t_event event, t_mesh *mesh, uint32_t *state)
{
	static t_bool			auto_rot = TRUE;

	if (*state & COLOR_TO_TEX || *state & TEX_TO_COLOR)
		event_texture(event, mesh, state);
	(*g_f[event])(event, mesh, state);
	if (event == OBJ_AUTO_ROT)
		auto_rot = (auto_rot == TRUE ? FALSE : TRUE);
	if (auto_rot == TRUE)
		auto_rotation(mesh);
}
