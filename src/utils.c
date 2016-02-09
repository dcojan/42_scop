#include <scop.h>

FILE	*open_file(char *path)
{
	FILE	*stream;

	printf("path = %s\n", path);
	stream = fopen(path, "r");
	if (stream == NULL)
	{
		perror("");
		return (NULL);
	}
	return stream;
}

void    print_vertice_array(GLfloat *array, size_t size)
{
    for (size_t i = 0; i < size; i += 3)
        printf("%f %f %f\n", array[i], array[i + 1], array[i + 2]);
}
void    print_element_array(GLushort *array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%hd ", array[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
    printf("\n");
}
