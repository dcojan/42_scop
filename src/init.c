/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:58 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:37:13 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		init_sdl(t_sdl *sdl_var)
{
	printf("init sdl\t");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	sdl_var->window = SDL_CreateWindow("OpenGL", 100, 100,
		WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	sdl_var->context = SDL_GL_CreateContext(sdl_var->window);
	printf("done.\n");
}

/*
** glEnable(GL_CULL_FACE);
*/

void		init_gl(void)
{
	printf("init gl\t");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	printf("done.\n");
}

void		init_glew(void)
{
	GLuint	vertex_buffer;

	printf("init glew\t");
	glewExperimental = GL_TRUE;
	glewInit();
	glGenBuffers(1, &vertex_buffer);
	printf("done.\n");
}
