#include <scop.h>

int			consume_end_of_line(FILE *stream)
{
	char    state;
	int     ret;

	while ((ret = fread(&state, 1, 1,stream)) != 0 && state != '\n')
	{
		// printf("%c", state);
	}
	return (ret);
}

t_obj		*load_obj(char *path)
{
	FILE		*stream;
	t_obj		*obj;

	printf("Opening file\n");
	if ((stream = open_file(path)) == NULL)
		return NULL;
	obj = new_obj();
	printf("Parsing file\n");
	while (1)
	{
		int ret = parse_label(obj, stream);
		if (ret == 0)
			break;
		if (ret == -1)
			return NULL;
	}
	// print_vertice_array(obj->vertex_data.v.vertices, obj->vertex_data.v.size);
	// print_element_array(obj->elements.f.element, obj->elements.f.size);
	if (obj->elements.f.size > 0)
		unpack_elements(obj);
	compute_normals(obj);
	// print_vertice_array(obj->vertex_data.vn.vertices, obj->vertex_data.vn.size);
	printf("Done.\n");
	return obj;
}
