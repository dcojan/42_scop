/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:05 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:34:29 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_vec4	vec3_to_vec4(t_vec3 *src, GLfloat w)
{
	t_vec4		dest;

	dest.data[0] = X(src);
	dest.data[1] = Y(src);
	dest.data[2] = Z(src);
	dest.data[3] = w;
	return (dest);
}
