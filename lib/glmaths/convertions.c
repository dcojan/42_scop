/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 09:29:55 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 11:23:55 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_vec3		quat_to_vec3(t_quat q)
{
	t_vec3		v;

	v.data[0] = q.data[0];
	v.data[1] = q.data[1];
	v.data[2] = q.data[2];
	return (v);
}

t_vec4		vec3_to_vec4(t_vec3 *src, GLfloat w)
{
	t_vec4		dest;

	dest.data[0] = PX(src);
	dest.data[1] = PY(src);
	dest.data[2] = PZ(src);
	dest.data[3] = w;
	return (dest);
}

t_vec3		vec4_to_vec3(t_vec4 src)
{
	t_vec3		dest;

	dest.data[0] = src.data[0];
	dest.data[1] = src.data[1];
	dest.data[2] = src.data[2];
	return (dest);
}

float		radians(float degree)
{
	return (degree * M_PI / 180);
}
