/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:42:27 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 16:38:14 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"

static FILE	*open_file(const char *path)
{
	FILE	*stream;

	stream = fopen(path, "r");
	if (stream == NULL)
	{
		perror(path);
		return (NULL);
	}
	return (stream);
}

int			check_tga(FILE *file_ptr)
{
	t_tga_header	head;

	fread(&(head.uchar_bad), sizeof(unsigned char), 1, file_ptr);
	fread(&(head.uchar_bad), sizeof(unsigned char), 1, file_ptr);
	fread(&(head.image_type_code), sizeof(unsigned char), 1, file_ptr);
	if (head.image_type_code != 2 && head.image_type_code != 3)
	{
		printf("this is a compressed tga\n");
		fclose(file_ptr);
		return (0);
	}
	fread(&(head.sint_bad), sizeof(short int), 1, file_ptr);
	fread(&(head.sint_bad), sizeof(short int), 1, file_ptr);
	fread(&(head.uchar_bad), sizeof(unsigned char), 1, file_ptr);
	fread(&(head.sint_bad), sizeof(short int), 1, file_ptr);
	fread(&(head.sint_bad), sizeof(short int), 1, file_ptr);
	return (1);
}

void		swap_color(t_tga_tex *tga_file, long image_size, int color_mode)
{
	unsigned char	color_swap;
	int				image_idx;

	image_idx = 0;
	while (image_idx < image_size)
	{
		color_swap = tga_file->data[image_idx];
		tga_file->data[image_idx] = tga_file->data[image_idx + 2];
		tga_file->data[image_idx + 2] = color_swap;
		image_idx += color_mode;
	}
}

t_tga_tex	*load_tga(const char *filename)
{
	t_tga_tex		*tga_file;
	FILE			*file_ptr;
	t_tga_header	head;
	int				color_mode;

	printf("loading %s\n", filename);
	if ((file_ptr = open_file(filename)) == NULL)
		printf("Error opening file\n");
	tga_file = (t_tga_tex*)malloc(sizeof(t_tga_tex));
	if (check_tga(file_ptr) == 0)
		return (NULL);
	fread(&tga_file->width, sizeof(short int), 1, file_ptr);
	fread(&tga_file->height, sizeof(short int), 1, file_ptr);
	fread(&(head.bit_count), sizeof(uint8_t), 1, file_ptr);
	fread(&(head.uchar_bad), sizeof(uint8_t), 1, file_ptr);
	color_mode = head.bit_count / 8;
	head.image_size = tga_file->width * tga_file->height * color_mode;
	tga_file->data = (uint8_t *)malloc(sizeof(uint8_t) * head.image_size);
	fread(tga_file->data, sizeof(uint8_t), head.image_size, file_ptr);
	swap_color(tga_file, head.image_size, color_mode);
	fclose(file_ptr);
	return (tga_file);
}
