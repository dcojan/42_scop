/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:48:27 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/17 14:15:24 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

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
	//
	// t_mat4x4 *m= new_mat4x4();
	// m->data[0][0] += mesh->origin.data[0];
	// m->data[1][1] += mesh->origin.data[1];
	// m->data[2][2] += mesh->origin.data[2];
	// t_mat4x4 *dest= new_mat4x4();
	// mul_mat4x4(rotation, m ,dest);
	// // mul_mat4x4(m, rotation ,dest);
	// m->data[0][0] -= mesh->origin.data[0];
	// m->data[1][1] -= mesh->origin.data[1];
	// m->data[2][2] -= mesh->origin.data[2];
	// t_mat4x4 *dest2= new_mat4x4();
	// mul_mat4x4(m, dest,dest2);
	// // mul_mat4x4(dest, m, dest2);

	rot_unif_id = glGetUniformLocation(mesh->shader_program, "Rotation");
	glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation->data)[0][0]));
	// glUniformMatrix4fv(rot_unif_id, 1, GL_FALSE, &((rotation->data)[0][0]));
	free(rotation);
}
