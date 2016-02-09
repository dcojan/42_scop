#include <scop.h>

int			label_comment(t_obj *obj, FILE *stream)
{
	int			ret;

	(void)obj;
	printf("comment\t");
	ret = consume_end_of_line(stream);
	return (ret);
}

int			label_mtllib(t_obj *obj, FILE *stream)
{
	char	name[256];
	int		ret;

	(void)obj;
	printf("mtllib\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	consume_end_of_line(stream);
	return (ret);
}

int			label_usemtl(t_obj *obj, FILE *stream)
{
	char name[256];
	int     ret;
	char    state;

	(void)obj;
	printf("usemtl\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	while ((ret = fread(&state, 1, 1,stream)) != 0 && state != '\n')
	{
		// printf("%c", state);
	}
	return (ret);
}

int		label_o(t_obj *obj, FILE *stream)
{
	char 	name[256];
	int		ret;

	(void)obj;
	printf("name\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	consume_end_of_line(stream);
	return (ret);
}
