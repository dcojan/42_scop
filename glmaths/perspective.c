/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:58 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:42:27 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmath.h>

t_mat4x4	*perspective(GLfloat fovy, GLfloat ratio, GLfloat near, GLfloat far)
{
	t_mat4x4	*mat;
	GLfloat		tan_half_angle;

	if (ratio == 0 || near == far)
	{
		printf("ratio == 0 or near == far\n");
		exit(-1);
	}
	mat = new_mat4x4();
	tan_half_angle = tan(fovy / 2.0f);
	(mat->data)[0][0] = 1.0f / (ratio * tan_half_angle);
	(mat->data)[1][1] = 1.0f / tan_half_angle;
	(mat->data)[2][2] = -(far + near) / (far - near);
	(mat->data)[2][3] = -1.0f;
	(mat->data)[3][2] = -(2.0f * far * near) / (far - near);
	(mat->data)[3][3] = 0.0f;
	return (mat);
}
