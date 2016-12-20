#ifndef RELIGHTER_CORE_RELIGHTABLEIMAGE_H
#define RELIGHTER_CORE_RELIGHTABLEIMAGE_H

#include <string>
#include <vector>
#include <io/FileReader.h>
#include "Sampler.h"

class RelightableImage
{
public:
	RelightableImage(const std::string& filepath);
	void resolve(const std::string& filepath, const std::vector<Sampler>& samplers);

private:
	RelightableImage(const RelightableImage& rhs);
	RelightableImage& operator=(const RelightableImage& rhs);
	FileReader m_reader;
	int m_width, m_height;
	int m_samples;
	std::vector<size_t> m_pixelOffsets;
};

#endif
