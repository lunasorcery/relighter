#ifndef RELIGHTER_CORE_SAMPLER_H
#define RELIGHTER_CORE_SAMPLER_H

#include <math/vec2.h>
#include <math/vec3.h>
#include "Texture.h"

class Sampler
{
public:
	Sampler(const TextureHandle tex);
	vec3 sample(const vec2& uv) const;

private:
	const TextureHandle m_tex;
};

#endif
