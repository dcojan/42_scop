/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:48:42 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/17 13:48:36 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_loader.h"

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

int			load_bmp_header(t_bmp_tex **bmp, FILE *stream)
{
	uint8_t		head[54];

	if (fread(head, 1, 54, stream) != 54 ||
				head[0] != 'B' || head[1] != 'M')
		return (0);
	*bmp = (t_bmp_tex*)malloc(sizeof(t_bmp_tex));
	(*bmp)->width = *(int*)&(head[0x12]);
	(*bmp)->height = *(int*)&(head[0x16]);
	if ((*bmp)->width > 720 || (*bmp)->height > 720)
	{
		free(*bmp);
		*bmp = NULL;
		return (0);
	}
	return (1);
}

t_bmp_tex	*load_bmp(const char *path)
{
	t_bmp_tex	*bmp;
	FILE		*stream;

	bmp = NULL;
	printf("Loading %s\t", path);
	if ((stream = open_file(path)) == NULL)
	{
		printf("Error opening file\n");
		return (NULL);
	}
	if (load_bmp_header(&bmp, stream))
	{
		bmp->image_size = bmp->width * bmp->height * 3;
		bmp->data = (uint8_t*)malloc(sizeof(uint8_t) * bmp->image_size);
		fread(bmp->data, 1, bmp->image_size, stream);
	}
	else
		printf("Not a correct BMP file\n");
	if (stream != NULL)
		fclose(stream);
	printf("Done\n");
	return (bmp);
}
