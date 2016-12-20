#include "RandHelper.h"
#include <cmath>
#include <random>
#include <math/constants.h>

float RandHelper::uniformFloat()
{
	// ew, replace with c++11 rand at some point
	return rand()/(float)RAND_MAX;
}

vec3 RandHelper::unitVec3()
{
	float theta = uniformFloat() * PI * 2.0f;
	float phi = acosf(2.0f * uniformFloat() - 1.0f);

	float z = cosf(phi);
	float x = sqrtf(1-z*z) * cosf(theta);
	float y = sqrtf(1-z*z) * sinf(theta);

	return vec3(x, y, z);
}

vec3 RandHelper::unitVec3OnHemisphere(const vec3& normal)
{
	vec3 unit = unitVec3();
	if (vec3::dot(unit, normal)<0)
	{
		return -unit;
	}
	return unit;
}
