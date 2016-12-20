#ifndef RELIGHTER_CORE_MATERIAL_H
#define RELIGHTER_CORE_MATERIAL_H

#include <memory>
#include <math/vec3.h>

struct Brdf
{
	enum T
	{
		Diffuse,
		Mirror,
		Emissive
	};
};

struct Material;
typedef std::shared_ptr<Material> MaterialHandle;

struct Material
{
	vec3 color;
	Brdf::T brdf;
	int texId;
	
	Material();
	
	bool isTextured() const;
	static MaterialHandle createTextured(int texId, Brdf::T brdf);
	static MaterialHandle createColored(const vec3& color, Brdf::T brdf);
};

#endif
