/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:16:53 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/15 17:31:28 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmath.h>

t_mat4x4 *lookAt(t_vec3 const *eye, t_vec3  const *center, t_vec3  const *up)
{
    t_vec3  s; //X
    t_vec3  u; //Y
    t_vec3  f; //Z

    // Z
    f = sub(*center, *eye);
    normalize(&f);

    //X
    s = cross(&f, up);
    normalize(&s);

    //Y
    u = cross(&s, &f);
    normalize(&u);

    // print_vec3(&f);
    // print_vec3(eye);
    // printf("%f\n",dot(&s, eye));

    t_mat4x4    *Result;
    Result = new_mat4x4();
    (Result->data)[0][0] = s.data[0];
    (Result->data)[1][0] = s.data[1];
    (Result->data)[2][0] = s.data[2];
    (Result->data)[0][1] = u.data[0];
    (Result->data)[1][1] = u.data[1];
    (Result->data)[2][1] = u.data[2];
    (Result->data)[0][2] = -f.data[0];
    (Result->data)[1][2] = -f.data[1];
    (Result->data)[2][2] = -f.data[2];
    (Result->data)[3][0] = -dot(&s, eye);
    (Result->data)[3][1] = -dot(&u, eye);
    (Result->data)[3][2] = dot(&f, eye);
    return Result;
}
