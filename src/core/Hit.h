#ifndef RELIGHTER_CORE_HIT_H
#define RELIGHTER_CORE_HIT_H

#include "Material.h"
#include "Vertex.h"

struct Hit
{
	MaterialHandle mat;
	Vertex vert;
	float dist;
	bool success;

	static Hit createFailed();
	static Hit createSuccess(const MaterialHandle mat, const Vertex& vert, float dist);
private:
	Hit(const MaterialHandle mat, const Vertex& vert, float dist, bool success);
};

#endif
