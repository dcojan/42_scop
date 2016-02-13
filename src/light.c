/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:09 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 17:25:25 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		set_light(GLfloat x, GLfloat y, GLfloat z, GLuint program)
{
	GLuint light_id;

	light_id = glGetUniformLocation(program, "light_position_worldspace");
	glUniform3f(light_id, x, y, z);
}
