#ifndef RELIGHTER_CORE_VERTEX_H
#define RELIGHTER_CORE_VERTEX_H

#include <math/vec2.h>
#include <math/vec3.h>

struct Vertex
{
	vec3 pos;
	vec3 nrm;
	vec2 uv;

	Vertex();
	Vertex(const vec3& pos, const vec3& nrm);
	Vertex(const vec3& pos, const vec3& nrm, const vec2& uv);
};

Vertex operator+(const Vertex& a, const Vertex& b);
Vertex operator-(const Vertex& a, const Vertex& b);
Vertex operator*(const Vertex& a, float b);

#endif
