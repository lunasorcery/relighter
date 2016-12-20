#include <cmath>
#include "Camera.h"

Camera::Camera(const vec3& pos, const vec3& target, const vec3& up, float fov, float aspect)
:
pos(pos),
fwd(vec3::normalize(target - pos)),
right(vec3::cross(fwd, up)),
up(vec3::cross(right, fwd)),
tanFovOverTwo(tanf(fov * .5f)),
aspect(aspect)
{ }

Ray Camera::getRay(const vec2& xy) const
{
	float x = tanFovOverTwo * xy.x * aspect;
	float y = tanFovOverTwo * xy.y;
	return Ray(pos, fwd+(x*right)+(y*up));
}
