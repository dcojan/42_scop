/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:53:36 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 16:26:03 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

uint8_t		test_event(SDL_Event *we, uint32_t type, SDL_Keycode key)
{
	if (type == 0 && key == 0)
		return (1);
	if (we->type == type && key == 0)
		return (1);
	if (type == SDL_KEYDOWN || type == SDL_KEYUP)
		return (we->type == type && we->key.keysym.sym == key);
	else if (type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP)
		return (we->type == type && we->button.button == key);
	return (0);
}

static const t_keyevent		g_keycodes[17] =
{
	{SDL_QUIT, 0, QUIT},
	{SDL_KEYUP, SDLK_ESCAPE, QUIT},
	{SDL_KEYUP, SDLK_r, OBJ_AUTO_ROT},
	{SDL_KEYDOWN, SDLK_q, OBJ_TRANS_X},
	{SDL_KEYDOWN, SDLK_a, OBJ_TRANS_X_REV},
	{SDL_KEYDOWN, SDLK_w, OBJ_TRANS_Y},
	{SDL_KEYDOWN, SDLK_s, OBJ_TRANS_Y_REV},
	{SDL_KEYDOWN, SDLK_e, OBJ_TRANS_Z},
	{SDL_KEYDOWN, SDLK_d, OBJ_TRANS_Z_REV},
	{SDL_KEYDOWN, SDLK_x, OBJ_TRANS_RESET},
	{SDL_KEYDOWN, SDLK_y, LIGHT_MORE},
	{SDL_KEYDOWN, SDLK_h, LIGHT_LESS},
	{SDL_KEYUP, SDLK_t, TOGGLE_TEXTURE},
	{SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT, START_CAMERA_MOVE},
	{SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT, STOP_CAMERA_MOVE},
	{SDL_MOUSEMOTION, 0, CAMERA_MOVE},
	{0, 0, NO_EVENT},
};

t_event		sdl_to_scop_event(SDL_Event *we)
{
	int							i;

	i = -1;
	while (++i < 17)
		if (test_event(we, g_keycodes[i].type, g_keycodes[i].code))
			break ;
	return (g_keycodes[i].event);
}

t_event		get_scop_event(void)
{
	static t_bool			click_down = FALSE;
	SDL_Event				we;
	t_event					event;

	if (!SDL_PollEvent(&we))
		return (NO_EVENT);
	event = sdl_to_scop_event(&we);
	if (event == START_CAMERA_MOVE)
		click_down = TRUE;
	if (event == STOP_CAMERA_MOVE)
		click_down = FALSE;
	if (click_down == FALSE && event == CAMERA_MOVE)
		return (NO_EVENT);
	return (event);
}
