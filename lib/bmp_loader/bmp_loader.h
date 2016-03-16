/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:52:04 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 14:31:04 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_LOADER_H
# define BMP_LOADER_H
# include <stdint.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct	s_bmp_tex
{
	char		*name;
	uint32_t	width;
	uint32_t	height;
	uint32_t	image_size;
	uint8_t		*data;
};
typedef struct s_bmp_tex	t_bmp_tex;

t_bmp_tex	*load_bmp(const char *path);
#endif
