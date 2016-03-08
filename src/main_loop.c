/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:10 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:15:49 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		main_loop(t_sdl *sdl_var, t_mesh *mesh)
{
	t_event			event;
	t_bool			auto_rot;
	double			next_game_tick;
	uint32_t		state;

	state = NO_STATE;
	next_game_tick = 0;
	auto_rot = TRUE;
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
		handle_event(event, mesh, &state);
		if (event == OBJ_AUTO_ROT)
			auto_rot = (auto_rot == TRUE ? FALSE : TRUE);
		if (auto_rot == TRUE)
			auto_rotation(mesh);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
