#include <scop.h>

void	compute_normals(t_obj *obj)
{
	printf("Computing normals.\n");
	obj->vertex_data.vn.vertices = (GLfloat*)malloc(sizeof(GLfloat) * obj->vertex_data.v.size);
	obj->vertex_data.vn.size = obj->vertex_data.v.size;
	for (size_t i = 0; i < obj->vertex_data.v.size; i+=9)
	{
		t_vec3  v, v2;
		t_vec3  *ia = (t_vec3*)&(obj->vertex_data.v.vertices[i]);
		t_vec3  *ib = (t_vec3*)&(obj->vertex_data.v.vertices[i + 3]);
		t_vec3  *ic = (t_vec3*)&(obj->vertex_data.v.vertices[i + 6]);
		sub(ib, ia, &v);
		sub(ic, ia, &v2);
		cross(&v, &v2, (t_vec3*)&(obj->vertex_data.vn.vertices[i]));
		normalize((t_vec3*)&(obj->vertex_data.vn.vertices[i]));
		memcpy(&(obj->vertex_data.vn.vertices[i + 3]), &(obj->vertex_data.vn.vertices[i]), sizeof(GLfloat) * 3);
		memcpy(&(obj->vertex_data.vn.vertices[i + 6]), &(obj->vertex_data.vn.vertices[i]), sizeof(GLfloat) * 3);
	}
}

void	unpack_elements(t_obj *obj)
{
	GLfloat     *new = (GLfloat *)malloc(sizeof(GLfloat) * (obj->elements.f.size * 3));
	size_t      size = obj->elements.f.size * 3;
	int         vindex = 0;

	printf("Unpacking elements\n");
	for (size_t i = 0; i < obj->elements.f.size; i++)
	{
		new[vindex] = obj->vertex_data.v.vertices[ obj->elements.f.element[i] * 3];
		new[vindex + 1] = obj->vertex_data.v.vertices[ obj->elements.f.element[i] * 3 + 1];
		new[vindex + 2] = obj->vertex_data.v.vertices[ obj->elements.f.element[i] * 3 + 2 ];
		vindex += 3;
	}
	free(obj->vertex_data.v.vertices);
	obj->vertex_data.v.vertices = new;
	obj->vertex_data.v.size = size;
	// print_vertice_array(obj->vertex_data.v.vertices, obj->vertex_data.v.size);
}

void    add_vec3(t_vec3 *vec, t_vertex *v)
{
	GLfloat		*new;

	new = (GLfloat *)malloc(sizeof(GLfloat) * (v->size + 3));
	if (v->size > 0)
		memcpy(new, v->vertices, sizeof(GLfloat) * v->size);
	new[v->size] = X(vec);
	new[v->size + 1] = Y(vec);
	new[v->size + 2] = Z(vec);
	if (v->vertices != NULL)
		free(v->vertices);
	v->vertices = new;
	v->size += 3;
}

void    add_element(GLushort *el, t_element *v, int nb)
{
    size_t size = (v->size + (3 * (nb - 2)));
    GLushort     *new = (GLushort *)malloc(sizeof(GLushort) * size);

    if (v->size > 0)
        memcpy(new, v->element, sizeof(GLushort) * v->size);
    new[v->size] = el[0] - 1;
    new[v->size + 1] = el[1] - 1;
    new[v->size + 2] = el[2] - 1;
    if (nb == 4)
    {
        printf("nb 4 !!\n");
        new[v->size + 3] = el[2] - 1;
        new[v->size + 4] = el[3] - 1;
        new[v->size + 5] = el[0] - 1;
    }
    if (v->element != NULL)
        free(v->element);
    v->element = new;
    v->size = size;
}

t_obj   *new_obj()
{
	t_obj   *obj = (t_obj*)malloc(sizeof(t_obj));
	obj->vertex_data.v.vertices = NULL;
	obj->vertex_data.v.size = 0;
	obj->vertex_data.vn.vertices = NULL;
	obj->vertex_data.vn.size = 0;
	obj->elements.f.element = NULL;
	obj->elements.f.size = 0;
	return obj;
}
