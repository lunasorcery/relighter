#include <vector>
#include <core/RelightableImage.h>
#include <core/Sampler.h>
#include <core/Texture.h>

int main()
{
	RelightableImage img("out.bin");

	TextureHandle colorWhite = Texture::create1pxColor(vec3(1, 1, 1));
	TextureHandle texRGB   = Texture::createFromFile("textures/rgb.png");
	TextureHandle texLenna = Texture::createFromFile("textures/lenna.png");
	TextureHandle texSky   = Texture::createFromFileHdr("textures/OpenfootageNEtHDRCow_small.hdr");

	std::vector<Sampler> samplers;
	samplers.push_back(Sampler(texSky));   // sky
	samplers.push_back(Sampler(texRGB));   // wall1
	samplers.push_back(Sampler(texLenna)); // wall2

	img.resolve(
		"out.png",
		samplers
	);

	return 0;
}
