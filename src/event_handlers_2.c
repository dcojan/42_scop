/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:56:31 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 14:56:48 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		event_zoom(t_event event, t_mesh *mesh, void *arg)
{
	static float	zoom = 1.0f;

	if (event == ZOOM_IN)
		zoom += 0.1f;
	else if (event == ZOOM_OUT)
		zoom -= 0.1f;
	set_projection(zoom, mesh->shader_program);
	(void)arg;
}

void		event_empty(t_event event, t_mesh *mesh, void *arg)
{
	(void)arg;
	(void)event;
	(void)mesh;
}

void		event_rotation(t_event event, t_mesh *mesh, void *arg)
{
	(void)arg;
	(void)event;
	auto_rotation(mesh);
}

void		event_texture(t_event event, t_mesh *mesh, void *arg)
{
	static float	i = 0.0f;
	GLuint			unif_id;
	t_state			*state;

	(void)event;
	state = (t_state*)arg;
	if (!(*state & COLOR_TO_TEX) && !(*state & TEX_TO_COLOR))
	{
		if (i >= 1.0f)
			*state |= COLOR_TO_TEX;
		else if (i <= 0.0f)
			*state |= TEX_TO_COLOR;
	}
	else
	{
		i += (*state == COLOR_TO_TEX ? -0.2f : 0.2f);
		if (*state == COLOR_TO_TEX)
			if (i <= 0.0f)
				*state &= ~COLOR_TO_TEX;
		if (*state == TEX_TO_COLOR)
			if (i >= 1.0f)
				*state &= ~TEX_TO_COLOR;
	}
	unif_id = glGetUniformLocation(mesh->shader_program, "texture_transition");
	glUniform1fv(unif_id, 1, &i);
}
