/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:03 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:32:19 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmath.h>

void	compute_normal(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *normal)
{
	t_vec3		tmp1;
	t_vec3		tmp2;

	tmp1 = sub(*v2, *v1);
	tmp2 = sub(*v3, *v1);
	*normal = cross(&tmp1, &tmp2);
	normalize(normal);
}

void     normalize(t_vec3 *src)
{
    GLfloat     d;

    d = sqrt(X(src) * X(src) + Y(src) * Y(src) + Z(src) * Z(src));
    if (d == 0)
    {
        return ;
    }
    X(src) = X(src) / d;
    Y(src) = Y(src) / d;
    Z(src) = Z(src) / d;
}

t_vec3     sub(t_vec3 const a, t_vec3 const b)
{
	t_vec3		dest;

	dest.data[0] = a.data[0] - b.data[0];
	dest.data[1] = a.data[1] - b.data[1];
	dest.data[2] = a.data[2] - b.data[2];
	return (dest);
}

t_vec3     cross(t_vec3 const *a, t_vec3 const *b)
{
	t_vec3		dest;

	dest.data[0] = Y(a) * Z(b) - Z(a) * Y(b);
	dest.data[1] = Z(a) * X(b) - X(a) * Z(b);
	dest.data[2] = X(a) * Y(b) - Y(a) * X(b);
	return (dest);
}

void        print_vec3(t_vec3 const *m)
{
    int     i;

    i = 0;
    while (i < 3)
    {
        printf("%f ", m->data[i]);
        i++;
    }
    printf("\n");
}

GLfloat     dot(t_vec3 const *a, t_vec3 const *b)
{
    GLfloat     dp;

    dp = X(a) * X (b) + Y(a) * Y(b) + Z(a) * Z(b);
    return dp;
}
