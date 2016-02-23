/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4x4operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:56 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/23 11:35:27 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmath.h>

t_mat4x4	*new_mat4x4(void)
{
	t_mat4x4	*mat;
	int			size;
	int			i;
	int			j;

	size = 16;
	mat = (t_mat4x4*)malloc(sizeof(t_mat4x4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			(mat->data)[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	(mat->data)[0][0] = 1.0f;
	(mat->data)[1][1] = 1.0f;
	(mat->data)[2][2] = 1.0f;
	(mat->data)[3][3] = 1.0f;
	return (mat);
}

void		mul_mat4x4(t_mat4x4 const *a, t_mat4x4 const *b, t_mat4x4 *dest)
{
	int		i;
	int		j;
	int		k;
	GLfloat	tmp;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp = 0;
			k = 0;
			while (k < 4)
			{
				tmp += (a->data)[i][k] * (b->data)[k][j];
				k++;
			}
			(dest->data)[i][j] = tmp;
			j++;
		}
		i++;
	}
}

t_mat4x4	*mat_translation(GLfloat x, GLfloat y, GLfloat z)
{
	t_mat4x4	*translation;

	translation = new_mat4x4();
	translation->data[3][0] += x;
	translation->data[3][1] += y;
	translation->data[3][2] += z;
	return (translation);
}
