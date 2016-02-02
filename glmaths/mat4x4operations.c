#include <glmath.h>

t_mat4x4    *new_mat4x4()
{
    t_mat4x4    *mat;
    int          size;

    size = 16;
    mat = (t_mat4x4*)malloc(sizeof(t_mat4x4));

    int     i;
    int     j;
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            (*mat)[i][j] = 0.0f;
            j++;
        }
        i++;
    }
    (*mat)[0][0] = 1.0f;
    (*mat)[1][1] = 1.0f;
    (*mat)[2][2] = 1.0f;
    (*mat)[3][3] = 1.0f;
    return (mat);
}

void     mul_mat4x4(t_mat4x4 const *a, t_mat4x4 const *b, t_mat4x4 *dest)
{
    int         i;
    int         j;
    int         k;
    GLfloat     tmp;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            tmp = 0;
            k = 0;
            while (k < 4)
            {
                tmp += (*a)[i][k] * (*b)[k][j];
                k++;
            }
            (*dest)[i][j] = tmp;
            j++;
        }
        i++;
    }
}

void        print_mat(t_mat4x4 const *m)
{
    int     i;
    int     j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            printf("%f ", (*m)[i][j]);
            j++;
        }
        i++;
        printf("\n");
    }
    printf("\n");
}
