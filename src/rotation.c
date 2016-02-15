/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:48:27 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 14:48:34 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		rotate_model(GLuint program, int axis, t_bool reverse, t_bool reset)
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
