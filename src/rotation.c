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

void		auto_rotation(t_mesh *mesh)
{
	static const float	angle = 30.0f / (float)FRAMES_PER_SECOND;
	static t_quat		rot = {{0, 0, 0, 1.0}};
	t_mat4x4			*rotation;
	t_quat				quat;
	GLuint				rot_unif_id;

	rotation = new_mat4x4();
	eul_to_quat(0.0f, radians(angle), 0.0f, &quat);
	rot = quat_x_quat(quat, rot);
	quat_to_mat4x4(rot, rotation);
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation->data)[0][0]));
	free(rotation);
}

void		rotate_model(t_mesh *mesh, int axis, t_bool reverse, t_bool reset)
{
	t_mat4x4			*rotation;
	t_quat				quat;
	static const float	amount = 1.0f;
	static float		angle[3] = {0.0f, 0.0f, 0.0f};
	GLuint				rot_unif_id;

	rotation = new_mat4x4();
	if (reset == TRUE)
		bzero(angle, sizeof(float) * 3);
	else
	{
		angle[axis] += (reverse == TRUE ? -amount : amount);
		if (angle[axis] >= 360)
			angle[axis] -= 360;
		else if (angle[axis] < 0)
			angle[axis] += 360;
	}
	eul_to_quat(radians(angle[0]), radians(angle[1]), radians(angle[2]), &quat);
	quat_to_mat4x4(quat, rotation);
	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation->data)[0][0]));
	free(rotation);
}
