#ifndef RELIGHTER_CORE_CAMERA_H
#define RELIGHTER_CORE_CAMERA_H

#include <math/vec2.h>
#include <math/vec3.h>
#include <core/Ray.h>

class Camera
{
public:
	Camera(const vec3& pos, const vec3& target, const vec3& up, float fov, float aspect);
	Ray getRay(const vec2& xy) const;
private:
	vec3 pos;
	vec3 fwd, right, up;
	float tanFovOverTwo;
	float aspect;
};

#endif
