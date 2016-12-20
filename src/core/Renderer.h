#ifndef RELIGHTER_CORE_RENDERER_H
#define RELIGHTER_CORE_RENDERER_H

#include <string>
#include <vector>
#include "Camera.h"
#include "ColorChain.h"
#include "Tri.h"

class Renderer
{
public:
	Renderer();
	void setSky(const MaterialHandle matSky);
	void addTri(const Tri& tri);
	void addQuad(const Tri& tri);
	void renderAndStreamIntoFile(int width, int height, int samples, const Camera& camera, const std::string& filepath);
private:
	void renderPixelSample(ColorChain& chain, float fx, float fy, const Camera& camera) const;
	void renderRay(ColorChain& chain, const Ray& ray, int depth = 0) const;
	Hit test(const Ray& ray) const;

	static const int kMaxDepth;

	MaterialHandle m_matSky;
	std::vector<Tri> m_scene;
};

#endif
