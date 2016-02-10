#include "glmath.h"

void	vec3_to_vec4(t_vec3 *src, float w, t_vec4 *dest)
{
	X(dest) = X(src);
	Y(dest) = Y(src);
	Z(dest) = Z(src);
	W(dest) = w;
}
