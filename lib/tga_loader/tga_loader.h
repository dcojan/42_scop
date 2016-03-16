/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:42:30 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 11:46:26 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_LOADER_H
# define TGA_LOADER_H

# include <stdint.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_tga_header
{
 uint8_t	ID_Length;
 uint8_t	ColorMapType;
 uint8_t	ImageType;
 // Color map specifications
 uint8_t	firstEntryIndex[2];
 uint8_t	colorMapLength[2];
 uint8_t	colorMapEntrySize;
 //image specification
 int16_t	xOrigin;
 int16_t	yOrigin;
 int16_t	width;
 int16_t	height;
 uint8_t	PixelDepth;
 uint8_t	ImageDescriptor;
}			t_tga_header;

typedef struct	s_tga_tex
{
	short			width;
	short			height;
	unsigned char	*data;
}				t_tga_tex;

t_tga_tex	*load_tga(const char* filename);

#endif
