#include <cmath>
#include "RandHelper.h"
#include "Renderer.h"
#include <io/FileWriter.h>
#include <math/constants.h>

const int Renderer::kMaxDepth = 3;

Renderer::Renderer()
:
m_matSky(nullptr),
m_scene()
{ }

void Renderer::setSky(const MaterialHandle matSky)
{
	m_matSky = matSky;
}

void Renderer::addTri(const Tri& tri)
{
	m_scene.push_back(tri);
}

void Renderer::addQuad(const Tri& tri)
{
	addTri(tri);
	addTri(tri.getDual());
}

void Renderer::renderAndStreamIntoFile(int width, int height, int samples, const Camera& camera, const std::string& filepath)
{
	FileWriter fw(filepath);
	{
		std::vector<size_t> cachedOffsetTable(width * height);

		fw.write<int>(width);
		fw.write<int>(height);
		fw.write<int>(samples);
		fw.write<int>(sizeof(size_t));

		size_t offsetTableStart = fw.position();
		for (int i = 0; i < width * height; ++i)
		{
			// allocate space for offset table in file
			fw.write(0x00AA11BB22CC33DDul);
		}
		
		ColorChain chain;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if ((x%32)==0)
				{
					printf("%d,%d / %dx%d\n", x, y, width, height);
				}
				
				size_t pixelDataStart = fw.position();
				cachedOffsetTable[y*width+x] = pixelDataStart;
				
				for (int i = 0; i < samples; ++i)
				{
					float fx = ((x + RandHelper::uniformFloat()) / width)  * 2.0f - 1.0f;
					float fy = ((y + RandHelper::uniformFloat()) / height) * 2.0f - 1.0f;
					fy *= -1;

					chain.reset();
					renderPixelSample(chain, fx, fy, camera);
					chain.reduceAndWriteToStream(fw);
				}
			}
		}
		
		// deferred offset table write
		fw.seek(offsetTableStart);
		for (int i = 0; i < width * height; ++i)
		{
			fw.write<size_t>(cachedOffsetTable[i]);
		}
	}
}

void Renderer::renderPixelSample(ColorChain& chain, float fx, float fy, const Camera& camera) const
{
	Ray ray = camera.getRay(vec2(fx, fy));
	renderRay(chain, ray);
}

void Renderer::renderRay(ColorChain& chain, const Ray& ray, int depth) const
{
	if (depth == kMaxDepth)
	{
		chain.pushZero();
		return;
	}

	Hit hit = test(ray);

	if (!hit.success)
	{
		// sky
		if (m_matSky)
		{
			vec2 uv(
				0.5f - (atan2(ray.d.z, ray.d.x) / PI) * 0.5f,
				0.5f - (asin(ray.d.y) / PI)
			);
			hit.mat = m_matSky;
			hit.vert.uv = uv;
			chain.push(hit, 1.0f);
		}
		else
		{
			chain.pushZero();
		}
		return;
	}
	
	if (hit.mat->brdf == Brdf::Emissive)
	{
		chain.push(hit, 1.0f);
		return;
	}
	
	float weight = 1.0f;
	vec3 newDir;

	if (hit.mat->brdf == Brdf::Mirror)
	{
		// specular
		newDir = vec3::reflect(ray.d, vec3::normalize(hit.vert.nrm));
	}
	else
	{
		// diffuse
		newDir = RandHelper::unitVec3OnHemisphere(hit.vert.nrm);
		weight = vec3::dot(newDir, vec3::normalize(hit.vert.nrm)) * 2.0f; // maybe div pi??????
	}
	
	chain.push(hit, weight);
	
	renderRay(chain, Ray(hit.vert.pos, newDir), depth + 1);
}

Hit Renderer::test(const Ray& ray) const
{
	Hit best = Hit::createFailed();
	for (auto& tri : m_scene)
	{
		Hit hit = tri.test(ray);
		if (hit.success && (!best.success || hit.dist < best.dist) && hit.dist > 0.00001f)
		{
			best = hit;
		}
	}
	return best;
}
