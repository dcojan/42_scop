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
			return (OBJ_ROT_Y_REV);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_d))
			return (OBJ_ROT_Y);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_w))
			return (OBJ_ROT_X_REV);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_s))
			return (OBJ_ROT_X);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_q))
			return (OBJ_ROT_Z_REV);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_e))
			return (OBJ_ROT_Z);
		else if (test_event(&we, SDL_KEYDOWN, SDLK_r))
			return (OBJ_ROT_RESET);
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

void		rotate_obj(GLuint program, int axis, t_bool reverse, t_bool reset)
{
	t_mat4x4			*rotation =  new_mat4x4();
	t_quat				quat;
	static const float	amount = 1.0f;
	static float		angle[3] = {0.0f, 0.0f, 0.0f};

	if (reset == TRUE)
		bzero(angle, sizeof(float) * 3);
	else
	{
		angle[axis] += (reverse == TRUE ? - amount : amount);
		if (angle[axis] >= 360)
			angle[axis] -= 360;
		else if (angle[axis] < 0)
			angle[axis] += 360;
	}
	eul_to_quat(radians(angle[0]), radians(angle[1]), radians(angle[2]), quat);
	quat_to_mat4x4(quat, *rotation);

	GLuint rot_unif_id = glGetUniformLocation(program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((*rotation)[0][0]));
	free(rotation);
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
			rotate_obj(program, 0, TRUE, FALSE);
		else if (event == OBJ_ROT_X)
			rotate_obj(program, 0, FALSE, FALSE);
		else if (event == OBJ_ROT_Y_REV)
			rotate_obj(program, 1, TRUE, FALSE);
		else if (event == OBJ_ROT_Y)
			rotate_obj(program, 1, FALSE, FALSE);
		else if (event == OBJ_ROT_Z_REV)
			rotate_obj(program, 2, TRUE, FALSE);
		else if (event == OBJ_ROT_Z)
			rotate_obj(program, 2, FALSE, FALSE);
		else if (event == OBJ_ROT_RESET)
			rotate_obj(program, 0, FALSE, TRUE);

		set_light(4, 4, 4, program);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_data.v.size);
		SDL_GL_SwapWindow(sdl_var->window);
	}
}
