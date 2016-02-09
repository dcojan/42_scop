#include <scop.h>

int		glsl_loader(char **text, char *path)
{
	char		buf[4096];
	FILE		*file;
	int			ret;
	int			current_size;
	char		*tmp;

	*text = NULL;
	current_size = 0;
	if ((file = open_file(path)) == NULL)
		return 0;
	while (1)
	{
		ret = fread(buf, 1, 4095, file);
		if (ret == -1)
			return 0;
		if (ret == 0)
			break;
		if (*text == NULL)
			*text = (char*)malloc(sizeof(char) * (ret + 1));
		else
		{
			tmp = *text;
			*text = (char*)malloc(sizeof(char) * (current_size + ret + 1));
			memcpy(*text, tmp, current_size);
			free(tmp);
		}
		memcpy(&((*text)[current_size]), buf, ret);
		current_size += ret;
		(*text)[current_size] = '\0';
		if (ret < 4095)
			break;
	}
	fclose(file);
	return 1;
}
