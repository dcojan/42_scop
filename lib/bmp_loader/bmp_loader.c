/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhiboux <nhiboux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:48:42 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/10 18:49:53 by nhiboux          ###   ########.fr       */
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

t_bmp_tex	*load_bmp(char *path)
{
	t_bmp_tex	*bmp;
	FILE		*stream;
	uint8_t		head[54];

	bmp = NULL;
	printf("Loading %s\t", path);
	if ((stream = open_file(path)) == NULL)
		printf("Error opening file\n");
	else if (fread(head, 1, 54, stream) == 54 &&
			head[0] == 'B' && head[1] == 'M' )
	{
		bmp = (t_bmp_tex*)malloc(sizeof(t_bmp_tex));
		bmp->width = *(int*)&(head[0x12]);
		bmp->height = *(int*)&(head[0x16]);
		if (bmp->width > 720 || bmp->height > 720)
		{
			printf("Not a correct BMP file\n");
			free(bmp);
			bmp = NULL;
		}
		else
		{
			bmp->image_size = bmp->width * bmp->height * 3;
			bmp->data = (uint8_t*)malloc(sizeof(uint8_t) * bmp->image_size);
			fread(bmp->data, 1, bmp->image_size, stream);
		}
	}
	else
		printf("Not a correct BMP file\n");
	if (stream != NULL)
		fclose(stream);
	printf("Done\n");
	return (bmp);
}
