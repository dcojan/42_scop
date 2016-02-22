/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 15:07:22 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:56:06 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>

# include <stdio.h>

# define WIDTH  		800
# define HEIGHT 		600

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_GLContext	context;
}					t_sdl;

void				init_sdl(t_sdl *sdl_var);
void				init_glew();
void				init_gl();
void				clean_sdl(t_sdl *sdl_var);
#endif
