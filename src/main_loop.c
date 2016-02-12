/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:10 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:12:22 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

// const int FRAMES_PER_SECOND = 60;
// const double SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

void		main_loop(t_sdl *sdl_var, GLuint program, t_obj *obj)
{
	SDL_Event		window_event;
	t_bool			quit;
	t_bool			click_down;
	int				mousex;
	int				mousey;
	int				mousebasex;
	int				mousebasey;

	click_down = FALSE;
	quit = FALSE;
	glUseProgram(program);
	glBindVertexArray(program);
	set_camera(0, 0, 5, program);
	set_light(4, 4, 4, program);
	printf("MAIN LOOP\n");
	while (quit == FALSE)
	{
	// 	currentTime = std::chrono::high_resolution_clock::now();
	// 	/// FRAMERATE CONTROL
	// 	next_game_tick += SKIP_TICKS;
	// 	sleep_time = next_game_tick - std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - t_start).count();
	// 	if (sleep_time >= 0)
	// 	{
	// 		usleep(sleep_time * 1000);
	// 		//flush all recorded moves during sleep time
	// 		SDL_FlushEvent(SDL_MOUSEMOTION);
	// 	}

		if (SDL_PollEvent(&window_event))
		{
			if (window_event.type == SDL_QUIT ||
				(window_event.type == SDL_KEYUP &&
				window_event.key.keysym.sym == SDLK_ESCAPE))
				quit = TRUE;
			else if (window_event.type == SDL_MOUSEBUTTONDOWN &&
				window_event.button.button == SDL_BUTTON_LEFT)
			{
				printf("LEFT CLICK DOWN\n");
				click_down = TRUE;
				SDL_GetMouseState(&mousebasex, &mousebasey);
				mousex = mousebasex;
				mousey = mousebasey;
			}
			else if (window_event.type == SDL_MOUSEBUTTONUP &&
				window_event.button.button == SDL_BUTTON_LEFT)
				{
					printf("LEFT CLICK UP\n");
					click_down = FALSE;
				}
			if (click_down == TRUE && window_event.type == SDL_MOUSEMOTION)
 				SDL_GetMouseState(&mousex, &mousey);
		}
		if (click_down == TRUE)
		{
			// printf("mouse relative position : %d %d\n", mousex - mousebasex, mousey - mousebasey);

			move_camera(mousex - mousebasex, mousey - mousebasey, program, 3.0f);
			mousebasex = mousex;
			mousebasey = mousey;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
