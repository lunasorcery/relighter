#ifndef RELIGHTER_CORE_COLORCHAIN_H
#define RELIGHTER_CORE_COLORCHAIN_H

#include <vector>
#include <io/FileReader.h>
#include <io/FileWriter.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include "Hit.h"
#include "Sampler.h"

class ColorChain
{
public:
	ColorChain();
	void reset();
	void pushZero();
	void push(const Hit& hit, float weight);
	void reduce();
	bool isZero() const;
	vec3 resolve(const std::vector<Sampler>& samplers) const;
	void reduceAndWriteToStream(FileWriter& fw);
	
	static ColorChain read(FileReader& fr);

private:
	struct TextureEntry
	{
		vec2 uv;
		float weight;
		int texId;

		TextureEntry(const vec2& uv, float weight, int texId);
		bool isTextured();
	};

	std::vector<TextureEntry> m_textureEntries;
	vec3 m_color;
};

#endif
