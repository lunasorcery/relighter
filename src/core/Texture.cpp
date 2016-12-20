#include "Texture.h"
#include <cstdio>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

Texture::Texture(int w, int h)
:
m_width(w),
m_height(h),
m_data(new vec3[w * h])
{ }

Texture::~Texture()
{
	delete[] m_data;
}

int Texture::getWidth()  const { return m_width;  }

int Texture::getHeight() const { return m_height; }

vec3 Texture::getPixel(int x, int y) const
{
	return m_data[y * m_width + x];
}

void Texture::setPixel(int x, int y, const vec3& value)
{
	m_data[y * m_width + x] = value;
}

void Texture::save(const std::string& filepath) const
{
	unsigned char* buffer = new unsigned char[m_width * m_height * 3];
	for(int y=0;y<m_height;++y)
	{
		for(int x=0;x<m_width;++x)
		{
			vec3 pixel = getPixel(x, y);
			buffer[(y*m_width+x)*3+0] = (unsigned char)(255.0f * pixel.x);
			buffer[(y*m_width+x)*3+1] = (unsigned char)(255.0f * pixel.y);
			buffer[(y*m_width+x)*3+2] = (unsigned char)(255.0f * pixel.z);
		}
	}
	stbi_write_png(filepath.c_str(), m_width, m_height, 3, buffer, m_width * 3);
	delete[] buffer;
}

TextureHandle Texture::createWithSize(int w, int h)
{
	Texture* tex = new Texture(w, h);
	return std::shared_ptr<Texture>(tex);
}

TextureHandle Texture::createFromFile(const std::string& filepath)
{
	int w, h, n;
	unsigned char *data = stbi_load(filepath.c_str(), &w, &h, &n, 3);
	if (data)
	{
		TextureHandle tex = createWithSize(w, h);
		unsigned char* ptr = data;
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				unsigned char r = *ptr++;
				unsigned char g = *ptr++;
				unsigned char b = *ptr++;
				tex->setPixel(x, y, vec3(
					powf(r / 255.f, 2.2f),
					powf(g / 255.f, 2.2f),
					powf(b / 255.f, 2.2f)
				));
			}
		}
		stbi_image_free(data);
		return tex;
	}
	else
	{
		printf("Failed to load texture %s\n", filepath.c_str());
		return createWithSize(1, 1);
	}
}

TextureHandle Texture::createFromFileHdr(const std::string& filepath)
{
	int w, h, n;
	float *data = stbi_loadf(filepath.c_str(), &w, &h, &n, 3);
	if (data)
	{
		TextureHandle tex = createWithSize(w, h);
		float* ptr = data;
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				float r = *ptr++;
				float g = *ptr++;
				float b = *ptr++;
				tex->setPixel(x, y, vec3(r, g, b));
			}
		}
		stbi_image_free(data);
		return tex;
	}
	else
	{
		printf("Failed to load texture %s\n", filepath.c_str());
		return createWithSize(1, 1);
	}
}

TextureHandle Texture::create1pxColor(const vec3& color)
{
	TextureHandle tex = createWithSize(1, 1);
	tex->setPixel(0, 0, color);
	return tex;
}
