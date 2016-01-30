#include <glmath.h>

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
void        print_vec3(t_vec3 const *m)
{
    int     i;

    i = 0;
    while (i < 3)
    {
        printf("%f ", (*m)[i]);
        i++;
    }
    printf("\n");
}
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

void     normalize(t_vec3 *src)
{
    GLfloat     d;

    d = sqrt(X(src) * X(src) + Y(src) * Y(src) + Z(src) * Z(src));
    X(src) = X(src) / d;
    Y(src) = Y(src) / d;
    Z(src) = Z(src) / d;
}

void     sub(t_vec3 const *a, t_vec3 const *b, t_vec3 *dest)
{
    X(dest) = X(a) - X(b);
    Y(dest) = Y(a) - Y(b);
    Z(dest) = Z(a) - Z(b);
}

void     cross(t_vec3 const *a, t_vec3 const *b, t_vec3 *dest)
{
    X(dest) = Y(a) * Z(b) - Z(a) * Y(b);
    Y(dest) = Z(a) * X(b) - X(a) * Z(b);
    Z(dest) = X(a) * Y(b) - Y(a) * X(b);
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

GLfloat     dot(t_vec3 const *a, t_vec3 const *b)
{
    GLfloat     dp;

    dp = X(a) * X (b) + Y(a) * Y(b) + Z(a) * Z(b);
    return dp;
}

t_mat4x4 *lookAt(t_vec3 const *eye, t_vec3  const *center, t_vec3  const *up)
{
    t_vec3  s; //X
    t_vec3  u; //Y
    t_vec3  f; //Z

    // Z
    sub(center, eye, &f);
    normalize(&f);

    //X
    cross(&f, up, &s);
    normalize(&s);

    //Y
    cross(&s, &f, &u);
    normalize(&u);

    // print_vec3(&f);
    // print_vec3(eye);
    // printf("%f\n",dot(&s, eye));

    t_mat4x4    *Result;
    Result = new_mat4x4();
    (*Result)[0][0] = s[0];
    (*Result)[1][0] = s[1];
    (*Result)[2][0] = s[2];
    (*Result)[0][1] = u[0];
    (*Result)[1][1] = u[1];
    (*Result)[2][1] = u[2];
    (*Result)[0][2] = -f[0];
    (*Result)[1][2] = -f[1];
    (*Result)[2][2] = -f[2];
    (*Result)[3][0] = -dot(&s, eye);
    (*Result)[3][1] = -dot(&u, eye);
    (*Result)[3][2] = dot(&f, eye);
    return Result;
}
