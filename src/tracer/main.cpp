#include <cstdio>
#include <core/Material.h>
#include <core/Renderer.h>
#include <core/Tri.h>

int main()
{
	const int kWidth   = 256;
	const int kHeight  = 256;
	const int kSamples = 64;

	printf("Creating materials\n");
	MaterialHandle matSky     = Material::createTextured(0, Brdf::Emissive);
	MaterialHandle matBlack   = Material::createColored(vec3(0), Brdf::Diffuse);
	MaterialHandle matFloor   = Material::createColored(vec3(1), Brdf::Diffuse);
	MaterialHandle MatMirror  = Material::createColored(vec3(.5f), Brdf::Mirror);
	MaterialHandle matTexWall1 = Material::createTextured(1, Brdf::Diffuse);
	MaterialHandle matTexWall2 = Material::createTextured(2, Brdf::Diffuse);

	printf("Creating model\n");
	Renderer renderer;
	renderer.setSky(matSky);
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3(-10, 0,-10), vec3(0, 1, 0)),
		Vertex(vec3(-10, 0, 10), vec3(0, 1, 0)),
		Vertex(vec3( 10, 0,-10), vec3(0, 1, 0))
	));
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3(-0.2f, 0.4f,-0.2f), vec3(0, 1, 0)),
		Vertex(vec3(-0.2f, 0.4f, 0.2f), vec3(0, 1, 0)),
		Vertex(vec3( 0.2f, 0.4f,-0.2f), vec3(0, 1, 0))
	));
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3(-0.2f, 0.4f, 0.2f), vec3(0, 0, 1)),
		Vertex(vec3(-0.2f, 0.0f, 0.2f), vec3(0, 0, 1)),
		Vertex(vec3( 0.2f, 0.4f, 0.2f), vec3(0, 0, 1))
	));
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3(0.2f, 0.4f, 0.2f), vec3(1, 0, 0)),
		Vertex(vec3(0.2f, 0.0f, 0.2f), vec3(1, 0, 0)),
		Vertex(vec3(0.2f, 0.4f,-0.2f), vec3(1, 0, 0))
	));
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3( 0.2f, 0.4f,-0.2f), vec3(0, 0, -1)),
		Vertex(vec3( 0.2f, 0.0f,-0.2f), vec3(0, 0, -1)),
		Vertex(vec3(-0.2f, 0.4f,-0.2f), vec3(0, 0, -1))
	));
	renderer.addQuad(Tri(
		matFloor,
		Vertex(vec3(-0.2f, 0.4f,-0.2f), vec3(-1, 0, 0)),
		Vertex(vec3(-0.2f, 0.0f,-0.2f), vec3(-1, 0, 0)),
		Vertex(vec3(-0.2f, 0.4f, 0.2f), vec3(-1, 0, 0))
	));
	renderer.addQuad(Tri(
		matTexWall1,
		Vertex(vec3(-1, 0, 1), vec3(1, 0, 0), vec2(0, 1)),
		Vertex(vec3(-1, 0,-1), vec3(1, 0, 0), vec2(1, 1)),
		Vertex(vec3(-1, 2, 1), vec3(1, 0, 0), vec2(0, 0))
	));
	renderer.addQuad(Tri(
		matTexWall2,
		Vertex(vec3(-1, 0,-1), vec3(0, 0, 1), vec2(0, 1)),
		Vertex(vec3( 1, 0,-1), vec3(0, 0, 1), vec2(1, 1)),
		Vertex(vec3(-1, 2,-1), vec3(0, 0, 1), vec2(0, 0))
	));
	renderer.addQuad(Tri(
		matBlack,
		Vertex(vec3(-1, 0,-1), vec3(-1, 0, 0), vec2(0, 1)),
		Vertex(vec3(-1, 0, 1), vec3(-1, 0, 0), vec2(1, 1)),
		Vertex(vec3(-1, 2,-1), vec3(-1, 0, 0), vec2(0, 0))
	));
	renderer.addQuad(Tri(
		matBlack,
		Vertex(vec3( 1, 0, -1), vec3(0, 0, -1), vec2(0, 1)),
		Vertex(vec3(-1, 0, -1), vec3(0, 0, -1), vec2(1, 1)),
		Vertex(vec3( 1, 2, -1), vec3(0, 0, -1), vec2(0, 0))
	));

	printf("Creating camera\n");
	Camera camera(
		vec3(3, 3, 3),
		vec3(0, 0.6f, 0),
		vec3(0, 1, 0),
		1.0f,
		(float)kWidth / kHeight
	);

	printf("Rendering\n");
	renderer.renderAndStreamIntoFile(kWidth, kHeight, kSamples, camera, "out.bin");

	return 0;
}
