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
	GLfloat	d;

	d = sqrt(PX(src) * PX(src) + PY(src) * PY(src) + PZ(src) * PZ(src));
	if (d == 0)
	{
		return ;
	}
	PX(src) = PX(src) / d;
	PY(src) = PY(src) / d;
	PZ(src) = PZ(src) / d;
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

	dest.data[0] = PY(a) * PZ(b) - PZ(a) * PY(b);
	dest.data[1] = PZ(a) * PX(b) - PX(a) * PZ(b);
	dest.data[2] = PX(a) * PY(b) - PY(a) * PX(b);
	return (dest);
}

void        print_vec3(t_vec3 const *m)
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

GLfloat     dot(t_vec3 const *a, t_vec3 const *b)
{
	GLfloat		dp;

	dp = PX(a) * PX(b) + PY(a) * PY(b) + PZ(a) * PZ(b);
	return dp;
}
