#include <cstdio>
#include <cmath>
#include "ColorChain.h"
#include "RelightableImage.h"

RelightableImage::RelightableImage(const std::string& filepath)
:
m_reader(filepath)
{
	m_width   = m_reader.read<int>();
	m_height  = m_reader.read<int>();
	m_samples = m_reader.read<int>();
	int size_size = m_reader.read<int>();
	//assert sizeof(size_t) == size_size
	m_pixelOffsets.reserve(m_width * m_height);
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			m_pixelOffsets.push_back(m_reader.read<size_t>());
		}
	}
}

vec3 Tonemap(const vec3& pixel)
{
	return vec3(
		powf(pixel.x, 1.f/2.2f),
		powf(pixel.y, 1.f/2.2f),
		powf(pixel.z, 1.f/2.2f)
	);
}
vec3 ClampColor(const vec3& pixel)
{
	return vec3(
		fminf(fmaxf(pixel.x, 0), 1),
		fminf(fmaxf(pixel.y, 0), 1),
		fminf(fmaxf(pixel.z, 0), 1)
	);
}

void RelightableImage::resolve(const std::string& filepath, const std::vector<Sampler>& samplers)
{
	m_reader.seek(m_pixelOffsets[0]);

	TextureHandle bmp = Texture::createWithSize(m_width, m_height);
	{
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				vec3 hdrPixel(0);
				for (int i = 0; i < m_samples; ++i)
				{
					ColorChain chain = ColorChain::read(m_reader);
					hdrPixel += chain.resolve(samplers);
				}
				hdrPixel /= m_samples;
				bmp->setPixel(x, y, ClampColor(Tonemap(hdrPixel)));
			}
		}
		bmp->save(filepath);
	}
}