/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glsl_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:12:54 by dcojan            #+#    #+#             */
/*   Updated: 2016/02/13 15:26:02 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glsl_loader.h"

static FILE	*open_file(const char *path)
{
	FILE	*stream;

	printf("path = %s\n", path);
	stream = fopen(path, "r");
	if (stream == NULL)
	{
		perror("");
		return (NULL);
	}
	return (stream);
}

void	maj_buffer(char **text, char buf[4094], int ret, int *current_size)
{
	char		*tmp;

	if (*text == NULL)
		*text = (char*)malloc(sizeof(char) * (ret + 1));
	else
	{
		tmp = *text;
		*text = (char*)malloc(sizeof(char) * (*current_size + ret + 1));
		memcpy(*text, tmp, *current_size);
		free(tmp);
	}
	memcpy(&((*text)[*current_size]), buf, ret);
	*current_size += ret;
	(*text)[*current_size] = '\0';
}

int		glsl_loader(char **text, const char *path)
{
	char		buf[4096];
	FILE		*file;
	int			ret;
	int			current_size;

	*text = NULL;
	current_size = 0;
	if ((file = open_file(path)) == NULL)
		return (0);
	while (1)
	{
		ret = fread(buf, 1, 4095, file);
		if (ret == -1)
			return (0);
		if (ret == 0)
			break ;
		maj_buffer(text, buf, ret, &current_size);
		if (ret < 4095)
			break ;
	}
	fclose(file);
	return (1);
}
