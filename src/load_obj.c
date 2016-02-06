#include <scop.h>
#include <fcntl.h>

FILE    *open_file(char *path)
{
    FILE *stream;

    printf("path = %s\n", path);
    stream = fopen(path, "r");
    if (stream == NULL)
    {
        perror("");
        return (NULL);
    }
    return stream;
}

void    add_vec3(t_vec3 *vec, t_vertex *v)
{
    GLfloat     *new = (GLfloat *)malloc(sizeof(GLfloat) * (v->size + 3));

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

t_obj    *load_obj(char *path)
{
    FILE     *stream;
    int     ret;
    int     vertice_count = 0;
    int     face_count = 0;

    printf("computing vertex buffer\n");
    printf("Opening file\n");
    if ((stream = open_file(path)) == NULL)
        return NULL;
    t_obj   *obj = new_obj();
    t_vec3      vec;
    printf("Parsing file\n");
    while (1)
    {
        char label[15];
        ret = fscanf(stream, "%s", label);
        if (ret == 0 || ret == -1)
            break;
        else if (strcmp(label,"#") == 0)
            printf("comment\t");
        else if (strcmp(label,"v") == 0)
        {
            // printf("vertex\t");
            ret = fscanf(stream, " %f %f %f", &(vec[0]), &(vec[1]), &(vec[2]));
            // printf("%d =>  %f %f %f\n", ret, vec[0], vec[1], vec[2]);
            vertice_count += ret;
            add_vec3(&vec, &(obj->vertex_data.v));
        }
        else if (strcmp(label,"f") == 0)
        {
            GLushort    el[4];
            // printf("face\t");
            ret = fscanf(stream, " %hd %hd %hd %hd", &(el[0]), &(el[1]), &(el[2]), &(el[3]));
            face_count += ret;
            if (ret == 4)
            {
                // printf("%d =>  %d %d %d %d\n", ret, el[0], el[1], el[2], el[3]);
                add_element(el, &(obj->elements.f), ret);
            }
            if (ret == 3)
            {
                // printf("%d =>  %d %d %d\n", ret, el[0], el[1], el[2]);
                add_element(el, &(obj->elements.f), ret);
                continue;
            }
        }
        else if (strcmp(label,"o") == 0)
        {
            char name[256];
            printf("name\t");
            ret = fscanf(stream, "%s", name);
            printf("%d =>  %s\n", ret, name);

        }
        else if (strcmp(label,"s") == 0)
        {
            char name[256];
            printf("smoothing group\t");
            ret = fscanf(stream, "%s", name);
            printf("%d =>  %s\n", ret, name);

        }
        else if (strcmp(label,"mtllib") == 0)
        {
            char name[256];
            printf("mtllib\t");
            ret = fscanf(stream, "%s", name);
            printf("%d =>  %s\n", ret, name);
        }
        else if (strcmp(label,"usemtl") == 0)
        {
            char name[256];
            printf("semtl\t");
            ret = fscanf(stream, "%s", name);
            printf("%d =>  %s\n", ret, name);
        }
        else
        {
            printf("parse error state `%s` not recognized\n", label);
            return NULL;
        }
        char    state;
        while ((ret = fread(&state, 1, 1,stream)) != 0 && state != '\n')
        {
            // printf("%c", state);
        }
        if (ret == 0 || ret == -1)
            break;
        // if (state == '\n')
            // printf("------------- \\n ------------\n");
    }
    // print_vertice_array(obj->vertex_data.v.vertices, obj->vertex_data.v.size);
    print_element_array(obj->elements.f.element, obj->elements.f.size);
    printf("vertice count : %zu  -  face count %zu\n",  obj->vertex_data.v.size,  obj->elements.f.size);

    printf("Unpacking elements\n");
    if (obj->elements.f.size > 0)
    {
        GLfloat     *new = (GLfloat *)malloc(sizeof(GLfloat) * (obj->elements.f.size * 3));
        size_t      size = obj->elements.f.size * 3;
        int         vindex = 0;
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
    // print_vertice_array(obj->vertex_data.v.vertices, obj->vertex_data.v.size);

    printf("Computing normals.\n");
    obj->vertex_data.vn.vertices = (GLfloat*)malloc(sizeof(GLfloat) * obj->vertex_data.v.size);
    obj->vertex_data.vn.size = obj->vertex_data.v.size;
    for (size_t i = 0; i < obj->vertex_data.v.size; i+=9)
    {
        // printf("i = %zu\n", i);
        t_vec3  v, v2;
        t_vec3  *ia = (t_vec3*)&(obj->vertex_data.v.vertices[i]);
        t_vec3  *ib = (t_vec3*)&(obj->vertex_data.v.vertices[i + 3]);
        t_vec3  *ic = (t_vec3*)&(obj->vertex_data.v.vertices[i + 6]);
        // printf("[ia] "); print_vec3(ia);
        // printf("[ib] "); print_vec3(ib);
        // printf("[ic] "); print_vec3(ic);
        sub(ib, ia, &v);
        // printf("[subv] "); print_vec3(&v);
        sub(ic, ia, &v2);
        // printf("[subv2] "); print_vec3(&v2);
        cross(&v, &v2, (t_vec3*)&(obj->vertex_data.vn.vertices[i]));

        // printf("[cross] ");print_vec3((t_vec3*)&(obj->vertex_data.vn.vertices[i]));

        normalize((t_vec3*)&(obj->vertex_data.vn.vertices[i]));
        // printf("[normalized] ");        print_vec3((t_vec3*)&(obj->vertex_data.vn.vertices[i]));


        memcpy(&(obj->vertex_data.vn.vertices[i + 3]), &(obj->vertex_data.vn.vertices[i]), sizeof(GLfloat) * 3);
        memcpy(&(obj->vertex_data.vn.vertices[i + 6]), &(obj->vertex_data.vn.vertices[i]), sizeof(GLfloat) * 3);
        // printf("[memcpy] ");        print_vec3((t_vec3*)&(obj->vertex_data.vn.vertices[i + 3]));
        // printf("[memcpy] ");        print_vec3((t_vec3*)&(obj->vertex_data.vn.vertices[i + 6]));
        // printf("-----------------\n");
    }
    printf("vertice count : %zu  -  face count %zu  -  normal count %zu \n",  obj->vertex_data.v.size,  obj->elements.f.size, obj->vertex_data.vn.size);

    // print_vertice_array(obj->vertex_data.vn.vertices, obj->vertex_data.vn.size);
    printf("Done.\n");
    // exit(0);
    return obj;
}
