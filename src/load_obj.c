#include <scop.h>
#include <fcntl.h>
//#include <errno.h>

int    load_obj(char *path)
{
    FILE     *stream;
    int     ret;
    char    state;

    printf("path = %s\n", path);

    stream = fopen(path, "r");
    if (stream == NULL)
    {
        perror("");
        return (0);
    }
    // printf("READING\n");

    t_vec3      vec;
    while (1)
    {
        ret = fread(&state, 1, 1,stream);
        if (ret == 0 || ret == -1)
            break;
        else if (state == '#')
            printf("\ncomment\n");
        else if (state == 'v')
        {
            printf("\nvertex\n");
            ret = fscanf(stream, " %f %f %f", &(vec[0]), &(vec[1]), &(vec[2]));
            printf("%d =>  %f %f %f\n", ret, vec[0], vec[1], vec[2]);
        }
        else if (state == 'f')
        {
            int a,b,c,d;
            printf("\nface\n");
            ret = fscanf(stream, " %d %d %d %d", &a, &b, &c, &d);
            if (ret == 4)
                printf("%d =>  %d %d %d %d\n", ret, a, b, c, d);
            if (ret == 3)
            {
                printf("%d =>  %d %d %d\n", ret, a, b, c);
                continue;
            }
        }
        else if (state == 'o')
            printf("\nname\n");
        while ((ret = fread(&state, 1, 1,stream)) != 0 && state != '\n')
        {
            // printf("%c", state);
        }
        if (ret == 0 || ret == -1)
            break;
        // ret = fscanf(stream, "#[^\n]");
        // printf("%d\n", ret);
    }
    return (1);
}
