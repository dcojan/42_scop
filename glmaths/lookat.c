#include <glmath.h>

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
