/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:52:04 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/22 11:23:09 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "glmath.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct	s_bmp_text
{
	char	*name;
	uint	width;
	uint	height;
	uint	image_size;
	uint8_t	data;
};
typedef s_bmp_text	t_bmp_text;

t_bmp_text	*load_bmp(char *path);
