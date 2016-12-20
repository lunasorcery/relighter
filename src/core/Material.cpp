#include "Material.h"

Material::Material()
:
color(0),
brdf(Brdf::Diffuse),
texId(-1)
{ }

bool Material::isTextured() const
{
	return (texId >= 0);
}

MaterialHandle Material::createTextured(int texId, Brdf::T brdf)
{
	MaterialHandle mat = std::make_shared<Material>();
	mat->texId = texId;
	mat->brdf = brdf;
	return mat;
}

MaterialHandle Material::createColored(const vec3& color, Brdf::T brdf)
{
	MaterialHandle mat = std::make_shared<Material>();
	mat->color = color;
	mat->brdf = brdf;
	mat->texId = -1;
	return mat;
}
