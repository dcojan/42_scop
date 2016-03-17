/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:42:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:25:16 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_LOADER_H
# define TGA_LOADER_H

# include <stdint.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_tga_tex
{
	short			width;
	short			height;
	unsigned char	*data;
}				t_tga_tex;

typedef struct	s_tga_header
{
	unsigned char	uchar_bad;
	short int		sint_bad;
	long			image_size;
	unsigned char	image_type_code;
	unsigned char	bit_count;
}				t_tga_header;

t_tga_tex		*load_tga(const char *filename);

#endif
