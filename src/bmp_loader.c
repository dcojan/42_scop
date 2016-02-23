/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:48:42 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/23 12:30:49 by dcojan           ###   ########.fr       */
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

void		compute_uv_coordinates(t_bmp_tex *tex)
{
	float		*uv;
	uint32_t	i;
	uint32_t	x;
	uint32_t	y;

	uv = (float *)malloc(sizeof(float) * (tex->width * tex->height * 2));
	i = 0;
	x = 0;
	y = 0;
	while (i < (tex->width * tex->height * 2))
	{
		uv[i] = x / tex->width;
		uv[i + 1] = y / tex->height;
		i += 2;
		x++;
		if (x == tex->width)
		{
			x = 0;
			y++;
		}
	}
	tex->uv = uv;
}

t_bmp_tex	*load_bmp(char *path)
{
	t_bmp_tex	*bmp;
	FILE		*stream;
	uint8_t		head[54];

	bmp = NULL;
	printf("Loading %s\n", path);
	if ((stream = open_file(path)) == NULL)
		printf("Error opening file\n");
	else if (fread(head, 1, 54, stream) == 54 &&
			head[0] == 'B' && head[1] == 'M')
	{
		bmp = (t_bmp_tex*)malloc(sizeof(t_bmp_tex));
		bmp->width = *(int*)&(head[0x12]);
		bmp->height = *(int*)&(head[0x16]);
		bmp->image_size = bmp->width * bmp->height * 3;
		bmp->data = (uint8_t*)malloc(sizeof(uint8_t) * bmp->image_size);
		fread(bmp->data, 1, bmp->image_size, stream);
	}
	else
		printf("Not a correct BMP file\n");
	if (stream != NULL)
		fclose(stream);
	compute_uv_coordinates(bmp);
	return (bmp);
}
