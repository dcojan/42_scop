/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:53 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 09:50:03 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_mat4x4	*look_at(t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up)
{
	t_vec3		s;
	t_vec3		u;
	t_vec3		f;
	t_mat4x4	*result;

	f = sub(*center, *eye);
	normalize(&f);
	s = cross(&f, up);
	normalize(&s);
	u = cross(&s, &f);
	normalize(&u);
	result = new_mat4x4();
	(result->data)[0][0] = s.data[0];
	(result->data)[1][0] = s.data[1];
	(result->data)[2][0] = s.data[2];
	(result->data)[0][1] = u.data[0];
	(result->data)[1][1] = u.data[1];
	(result->data)[2][1] = u.data[2];
	(result->data)[0][2] = -f.data[0];
	(result->data)[1][2] = -f.data[1];
	(result->data)[2][2] = -f.data[2];
	(result->data)[3][0] = -dot(&s, eye);
	(result->data)[3][1] = -dot(&u, eye);
	(result->data)[3][2] = dot(&f, eye);
	return (result);
}
