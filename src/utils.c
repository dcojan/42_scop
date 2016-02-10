#include <scop.h>

FILE	*open_file(const char *path)
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

void	print_vertice_array(GLfloat *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		printf("%f %f %f\n", array[i], array[i + 1], array[i + 2]);
		i += 3;
	}
}

void	print_element_array(GLushort *array, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		printf("%hd ", array[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
		i++;
	}
	printf("\n");
}
