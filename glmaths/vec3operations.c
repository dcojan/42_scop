#include <glmath.h>

void     normalize(t_vec3 *src)
{
    GLfloat     d;

    d = sqrt(X(src) * X(src) + Y(src) * Y(src) + Z(src) * Z(src));
    if (d == 0)
    {
        return ;
    }
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

GLfloat     dot(t_vec3 const *a, t_vec3 const *b)
{
    GLfloat     dp;

    dp = X(a) * X (b) + Y(a) * Y(b) + Z(a) * Z(b);
    return dp;
}
