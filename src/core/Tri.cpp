#include "Tri.h"

Tri::Tri(const MaterialHandle mat, const Vertex& v0, const Vertex& v1, const Vertex& v2)
:
mat(mat),
o(v0),
e1(v1-v0),
e2(v2-v0),
n(vec3::cross(e1.pos, e2.pos))
{ }

Hit Tri::test(const Ray& ray) const
{
	const float EPSILON = 0.0001f;
	Hit fail = Hit::createFailed();

	if (vec3::dot(ray.d, n) > 0)
		return fail;

	vec3 P = vec3::cross(ray.d, e2.pos);

	float det = vec3::dot(e1.pos, P);

	if (det > -EPSILON && det < EPSILON)
		return fail;
	float inv_det = 1.0f / det;

	vec3 T = ray.o - o.pos;

	float u = vec3::dot(T, P) * inv_det;

	if (u < 0.0f || u > 1.0f)
		return fail;

	vec3 Q = vec3::cross(T, e1.pos);

	float v = vec3::dot(ray.d, Q) * inv_det;

	if (v < 0.0f || v > 1.0f || u+v > 1.0f)
		return fail;

	float t = vec3::dot(e2.pos, Q) * inv_det;

	if (t > EPSILON)
	{
		return Hit::createSuccess(mat, interpolateVertex(u, v), t);
	}

	return fail;
}

Tri Tri::getDual() const
{
	return Tri(
		mat,
		o + e1 + e2,
		o + e2,
		o + e1
	);
}

Vertex Tri::interpolateVertex(float u, float v) const
{
	return o + (e1 * u) + (e2 * v);
}
