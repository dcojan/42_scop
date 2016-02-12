/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:17:03 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/12 17:17:04 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmath.h>

void	compute_normal(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *normal)
{
	t_vec3		tmp1;
	t_vec3		tmp2;

	sub(*v2, *v1, tmp1);
	sub(*v3, *v1, tmp2);
	cross(&tmp1, &tmp2, normal);
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

void     sub(t_vec3 const a, t_vec3 const b, t_vec3 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

void     cross(t_vec3 const *a, t_vec3 const *b, t_vec3 *dest)
{
    X(dest) = Y(a) * Z(b) - Z(a) * Y(b);
    Y(dest) = Z(a) * X(b) - X(a) * Z(b);
    Z(dest) = X(a) * Y(b) - Y(a) * X(b);
}

void        print_vec3(t_vec3 const *m)
{
    int     i;

    i = 0;
    while (i < 3)
    {
        printf("%f ", (*m)[i]);
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
