#include "ColorChain.h"

ColorChain::ColorChain()
:
m_textureEntries(),
m_color(1.0f)
{ }

void ColorChain::reset()
{
	m_textureEntries.clear();
	m_color = vec3(1.0f);
}

void ColorChain::pushZero()
{
	m_textureEntries.clear();
	m_color = vec3(0.0f);
}

void ColorChain::push(const Hit& hit, float weight)
{
	if (hit.mat->isTextured())
		m_textureEntries.push_back(TextureEntry(hit.vert.uv, weight, hit.mat->texId));
	else
		m_color *= hit.mat->color * weight;
}

void ColorChain::reduce()
{
	if (m_color.isZero())
	{
		m_textureEntries.clear();
		return;
	}

	bool areAnyZeroWeightTextures = false;
	for (auto& entry : m_textureEntries)
	{
		areAnyZeroWeightTextures |= (entry.weight <= 0);
	}

	if (areAnyZeroWeightTextures)
	{
		m_textureEntries.clear();
		m_color = vec3(0);
	}
}

bool ColorChain::isZero() const
{
	if (!m_color.isZero())
		return false;

	if (m_textureEntries.size() > 0)
		return false;

	return true;
}

vec3 ColorChain::resolve(const std::vector<Sampler>& samplers) const
{
	if (m_textureEntries.size() == 0)
		return m_color;

	if (m_color.isZero())
		return m_color;

	vec3 buffer = m_color;
	for (auto& entry : m_textureEntries)
	{
		buffer *= samplers[entry.texId].sample(entry.uv) * entry.weight;
	}
	return buffer;
}

void ColorChain::reduceAndWriteToStream(FileWriter& fw)
{
	reduce();

	uint8_t type;
	if (isZero())
	{
		type = 0;
	}
	else if (m_textureEntries.size() == 0)
	{
		type = 1;
	}
	else
	{
		type = 2;
	}

	fw.write<uint8_t>(type);
	if (!isZero())
	{
		fw.write<vec3>(m_color);
		if (m_textureEntries.size() > 0)
		{
			fw.write<int>(m_textureEntries.size());
			for (auto& entry : m_textureEntries)
			{
				fw.write<vec2>(entry.uv);
				fw.write<float>(entry.weight);
				fw.write<int>(entry.texId);
			}
		}
	}
}

ColorChain ColorChain::read(FileReader& fr)
{
	uint8_t type = fr.read<uint8_t>();
	ColorChain chain;
	switch(type)
	{
		case 0:
		default:
		{
			chain.m_color = vec3(0,0,0);
			chain.m_textureEntries.clear();
			break;
		}
		case 1:
		{
			chain.m_color = fr.read<vec3>();
			chain.m_textureEntries.clear();
			break;
		}
		case 2:
		{
			chain.m_color = fr.read<vec3>();
			int numTextureEntries = fr.read<int>();
			chain.m_textureEntries.reserve(numTextureEntries);
			for (int i = 0; i < numTextureEntries; ++i)
			{
				vec2 uv = fr.read<vec2>();
				float weight = fr.read<float>();
				int texId = fr.read<int>();
				chain.m_textureEntries.push_back(TextureEntry(uv, weight, texId));
			}
			break;
		}
	}
	return chain;
}

ColorChain::TextureEntry::TextureEntry(const vec2& uv, float weight, int texId)
:
uv(uv),
weight(weight),
texId(texId)
{ }
