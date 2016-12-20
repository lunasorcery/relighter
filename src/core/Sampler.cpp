#include "Sampler.h"

Sampler::Sampler(const TextureHandle tex)
:
m_tex(tex)
{ }

vec3 Sampler::sample(const vec2& uv) const
{
	int w = m_tex->getWidth();
	int h = m_tex->getHeight();
	int x = (int)(uv.x * w) % w;
	int y = (int)(uv.y * h) % h;
	if (x<0)x+=w;
	if (y<0)y+=h;
	return m_tex->getPixel(x, y);
}
