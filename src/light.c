/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:13:09 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 11:44:16 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		set_light(GLfloat x, GLfloat y, GLfloat z, GLuint program)
{
	GLuint light_id;

	light_id = glGetUniformLocation(program, "light_position_worldspace");
	glUniform3f(light_id, x, y, z);
}

void		init_light_power(t_mesh *mesh)
{
	int				id;
	GLfloat			light_power;

	id = glGetUniformLocation(mesh->shader_program, "LightPower");
	light_power = LIGHT_POWER;
	glUniform1fv(id, 1, &light_power);
}
