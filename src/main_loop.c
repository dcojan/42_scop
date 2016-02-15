/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:10 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 17:25:06 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

uint8_t		test_event(SDL_Event *we, uint32_t type, SDL_Keycode key)
{
	if (we->type == type && key == 0)
		return (1);
	if (we->type == type && (type == SDL_KEYDOWN || type == SDL_KEYUP))
		return (we->key.keysym.sym == key);
	else if (type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP)
		return (we->type == type && we->button.button == key);
	return (0);
}

t_event		get_event()
{
	static t_bool			click_down = FALSE;
	SDL_Event				we;

	if (SDL_PollEvent(&we))
	{
		if (test_event(&we, SDL_QUIT, 0) || test_event(&we, SDL_KEYUP, SDLK_ESCAPE))
			return (QUIT);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_a))
			return (OBJ_ROT_X_REV);
		else if (test_event(&we, SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT))
		{
			click_down = TRUE;
			return (START_CAMERA_MOVE);
		}
		else if (test_event(&we, SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT))
			click_down = FALSE;
		if (click_down == TRUE && we.type == SDL_MOUSEMOTION)
			return (CAMERA_MOVE);
	}
	return (NO_EVENT);
}

void		rotate_obj(GLuint program, t_event event)
{
	(void)event;
	t_mat4x4			*rotation =  new_mat4x4();
	t_quat				quat;
	static const float	amount = 1.0f;
	static float		angle = 0.0f;
	t_vec3				axis = {0, 1, 0};

	angle += amount;
	if (angle >= 360)
		angle -= 360;
	angleAxis(radians(angle), &axis, &quat);
	quat_to_mat4x4(quat, *rotation);

	GLuint rot_unif_id = glGetUniformLocation(program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((*rotation)[0][0]));
}

void		main_loop(t_sdl *sdl_var, GLuint program, t_obj *obj)
{
	int				mousex;
	int				mousey;
	int				mousebasex;
	int				mousebasey;
	t_event			event;

	event = NO_EVENT;
	glUseProgram(program);
	glBindVertexArray(program);
	set_camera(0, 0, 5, program);
	t_mat4x4		*rotation =  new_mat4x4();

	GLuint rot_unif_id = glGetUniformLocation(program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((*rotation)[0][0]));

	printf("MAIN LOOP\n");
	while (event != QUIT)
	{
		event = get_event();
		if (event == START_CAMERA_MOVE)
		{
			SDL_GetMouseState(&mousebasex, &mousebasey);
			mousex = mousebasex;
			mousey = mousebasey;
		}
		else if (event == CAMERA_MOVE)
		{
			SDL_GetMouseState(&mousex, &mousey);
			move_camera(mousex - mousebasex, mousey - mousebasey, program, 3.0f);
			mousebasex = mousex;
			mousebasey = mousey;
		}
		else if (event == OBJ_ROT_X_REV)
			rotate_obj(program, event);
		set_light(4, 4, 4, program);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
