/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:10 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 16:25:01 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		draw_obj(t_obj *obj)
{
	glBindVertexArray(obj->vaoid);
	glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
}

void		set_camera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLuint progid)
{
	GLuint			view_unif_id;
	t_mat4x4		*view;

	set_projection(1.0f, progid);
	view = view_matrix(eyex, eyey, eyez);
	view_unif_id = glGetUniformLocation(progid, "View");
	glUniformMatrix4fv(view_unif_id, 1, GL_FALSE, &((view->data)[0][0]));
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
	init_light_power(mesh);
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
