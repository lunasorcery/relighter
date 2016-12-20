#include "Hit.h"

Hit::Hit(const MaterialHandle mat, const Vertex& vert, float dist, bool success)
:
mat(mat),
vert(vert),
dist(dist),
success(success)
{ }

Hit Hit::createFailed()
{
	return Hit(nullptr, Vertex(), 0, false);
}

Hit Hit::createSuccess(const MaterialHandle mat, const Vertex& vert, float dist)
{
	return Hit(mat, vert, dist, true);
}
