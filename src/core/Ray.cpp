#include "Ray.h"

Ray::Ray(const vec3& o, const vec3& d)
:
o(o),
d(vec3::normalize(d))
{ }
