#ifndef RELIGHTER_CORE_TRI_H
#define RELIGHTER_CORE_TRI_H

#include "Hit.h"
#include "Material.h"
#include "Ray.h"
#include "Vertex.h"

class Tri
{
public:
	Tri(const MaterialHandle mat, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	Hit test(const Ray& ray) const;
	Tri getDual() const;

private:
	Vertex interpolateVertex(float u, float v) const;

	const MaterialHandle mat;
	Vertex o, e1, e2;
	vec3 n;
};

#endif
