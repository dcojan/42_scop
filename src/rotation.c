/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:48:27 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:18:56 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	auto_rotation(t_mesh *mesh)
{
	static const float	angle = 30.0f / (float)FRAMES_PER_SECOND;
	static t_quat		rot = {{0, 0, 0, 1.0}};
	t_mat4x4			rotation;
	t_quat				quat;
	GLuint				rot_unif_id;

	init_mat4x4(&rotation);
	eul_to_quat(0.0f, radians(angle), 0.0f, &quat);
	rot = quat_x_quat(quat, rot);
	quat_to_mat4x4(rot, &rotation);
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation.data)[0][0]));
}

void	translate_model(t_mesh *mesh, int axis, t_bool reverse, t_bool reset)
{
	static t_mat4x4		translation;
	static const float	amount = 0.1f;
	GLuint				rot_unif_id;

	if (translation.data[0][0] == 0)
		init_mat4x4(&translation);
	if (reset == TRUE)
	{
		translation.data[3][0] = 0;
		translation.data[3][1] = 0;
		translation.data[3][2] = 0;
	}
	else
		translation.data[3][axis] += (reverse == TRUE ? -amount : amount);
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "PostTranslation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((translation.data)[0][0]));
}
