#include <scop.h>

static int	(*const g_func_tab[7])(t_obj *obj, FILE *stream) =
{
	&label_comment,
	&label_v,
	&label_f,
	&label_o,
	&label_s,
	&label_mtllib,
	&label_usemtl,
};

int			parse_label(t_obj *obj, FILE *stream)
{
	static char		*tab[7] = {"#", "v", "f", "o", "s", "mtllib", "usemtl"};
	int				i;
	char			label[15];
	int				ret;

	ret = fscanf(stream, "%s", label);
	if (ret == EOF)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (strcmp(tab[i], label) == 0)
			return (*g_func_tab[i])(obj, stream);
		i++;
	}
	printf("parse error state `%s` not recognized\n", label);
	return (-1);
}

int			label_f(t_obj *obj, FILE *stream)
{
	int			ret;
	GLushort	el[4];

	ret = fscanf(stream, " %hd %hd %hd %hd",
		&(el[0]), &(el[1]), &(el[2]), &(el[3]));
	// printf("%d =>  %d %d %d %d\n", ret, el[0], el[1], el[2], el[3]);
	add_element(el, &(obj->elements.f), ret);
	return (ret);
}

int			label_s(t_obj *obj, FILE *stream)
{
	int		ret;
	char	name[256];

	(void)obj;
	printf("smoothing group\t");
	ret = fscanf(stream, "%s", name);
	printf("%d =>  %s\n", ret, name);
	return (ret);
}

int			label_v(t_obj *obj, FILE *stream)
{
	t_vec3		vec;
	int			ret;

	// printf("vertex\t");
	ret = fscanf(stream, " %f %f %f", &(vec[0]), &(vec[1]), &(vec[2]));
	// printf("%d =>  %f %f %f\n", ret, vec[0], vec[1], vec[2]);
	add_vec3(&vec, &(obj->vertex_data.v));
	return (ret);
}
