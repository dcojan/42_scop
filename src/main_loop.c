/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:10 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/09 19:41:55 by nhiboux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		draw_obj(t_obj* obj)
{
	glBindVertexArray(obj->vaoid);
	glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
}

void		main_loop(t_sdl *sdl_var, t_mesh *mesh)
{
	t_event			event;
	double			next_game_tick;
	uint32_t		state;
	t_obj			*obj;

	state = NO_STATE;
	next_game_tick = 0;
	event = NO_EVENT;
	set_camera(CAM_X, CAM_Y, CAM_Z, mesh->shader_program);
	set_light(LIGHT_X, LIGHT_Y, LIGHT_Z, mesh->shader_program);
	int id = glGetUniformLocation(mesh->shader_program, "LightPower");
	GLfloat	light_power = LIGHT_POWER;
	glUniform1fv(id, 1, &light_power);
	while (event != QUIT)
	{
		framerate_control(&next_game_tick);
		event = get_scop_event();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		handle_event(event, mesh, &state);
		obj = mesh->objs;
		while (obj != NULL)
		{
			draw_obj(obj);
			obj = obj->next;
		}
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
