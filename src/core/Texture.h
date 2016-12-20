#ifndef RELIGHTER_CORE_TEXTURE_H
#define RELIGHTER_CORE_TEXTURE_H

#include <memory>
#include <string>
#include <math/vec3.h>

class Texture;
typedef std::shared_ptr<Texture> TextureHandle;

class Texture
{
public:
	int getWidth() const;
	int getHeight() const;
	vec3 getPixel(int x, int y) const;
	void setPixel(int x, int y, const vec3& value);
	void save(const std::string& filepath) const;

	static TextureHandle createWithSize(int w, int h);
	static TextureHandle createFromFile(const std::string& filepath);
	static TextureHandle createFromFileHdr(const std::string& filepath);
	static TextureHandle create1pxColor(const vec3& color);
	~Texture();
private:
	Texture(int w, int h);
	Texture(const Texture& rhs);
	Texture& operator=(const Texture& rhs);
	int m_width, m_height;
	vec3* m_data;
};

#endif
