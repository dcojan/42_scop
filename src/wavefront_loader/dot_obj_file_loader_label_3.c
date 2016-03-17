/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_obj_file_loader_label_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:15:20 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:41:04 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavefront_loader.h"

int			label_l(t_mesh *mesh, char *str, t_f_pos *arg)
{
	(void)mesh;
	(void)str;
	(void)arg;
	return (1);
}

int			label_g(t_mesh *mesh, char *str, t_f_pos *arg)
{
	char	name[256];
	char	s[15];
	int		ret;

	(void)arg;
	(void)mesh;
	ret = sscanf(str, "%s %s", s, name);
	if (ret != 2)
		return (-1);
	return (ret);
}

int			label_s(t_mesh *mesh, char *str, t_f_pos *arg)
{
	int		ret;
	char	name[256];

	(void)mesh;
	(void)arg;
	str = &(str[1]);
	ret = sscanf(str, "%s", name);
	if (ret != 1)
		return (-1);
	return (1);
}
