#ifndef RELIGHTER_CORE_RAY_H
#define RELIGHTER_CORE_RAY_H

#include <math/vec3.h>

struct Ray
{
	vec3 o, d;

	Ray(const vec3& o, const vec3& d);
};

#endif
