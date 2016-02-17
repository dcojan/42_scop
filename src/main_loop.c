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

#include <scop.h>

void		main_loop(t_sdl *sdl_var, t_mesh *mesh)
{
	t_event			event;

	event = NO_EVENT;
	set_camera(0, 0, 5, mesh->shader_program);
	printf("MAIN LOOP\n");
	while (event != QUIT)
	{
		event = get_scop_event();
		handle_event(event, mesh);
		set_light(4, 4, 4, mesh->shader_program);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
