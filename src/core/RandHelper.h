#ifndef RELIGHTER_CORE_RANDHELPER_H
#define RELIGHTER_CORE_RANDHELPER_H

#include <math/vec3.h>

namespace RandHelper
{
	float uniformFloat();
	vec3 unitVec3();
	vec3 unitVec3OnHemisphere(const vec3& normal);
};

#endif
