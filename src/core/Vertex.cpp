#include "Vertex.h"

Vertex::Vertex()
:
pos(0),
nrm(0),
uv(0)
{ }

Vertex::Vertex(const vec3& pos, const vec3& nrm)
:
pos(pos),
nrm(nrm),
uv(0)
{ }

Vertex::Vertex(const vec3& pos, const vec3& nrm, const vec2& uv)
:
pos(pos),
nrm(nrm),
uv(uv)
{ }

Vertex operator+(const Vertex& a, const Vertex& b)
{
	return Vertex(a.pos + b.pos, a.nrm + b.nrm, a.uv + b.uv);
}

Vertex operator-(const Vertex& a, const Vertex& b)
{
	return Vertex(a.pos - b.pos, a.nrm - b.nrm, a.uv - b.uv);
}

Vertex operator*(const Vertex& a, float b)
{
	return Vertex(a.pos * b, a.nrm * b, a.uv * b);
}
