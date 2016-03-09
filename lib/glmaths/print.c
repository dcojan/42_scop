/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 09:35:16 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:37:22 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void		print_vec3(t_vec3 const *m)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		printf("%f ", m->data[i]);
		i++;
	}
	printf("\n");
}

void		print_mat(t_mat4x4 const *m)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", (m->data)[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("\n");
}
