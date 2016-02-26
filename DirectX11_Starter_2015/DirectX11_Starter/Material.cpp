#include "Material.h"
#include "Render.h"

Material::Material(SimpleVertexShader* newVertexShader, SimplePixelShader* newPixelShader)
{
	vertexShader = newVertexShader;
	pixelShader = newPixelShader;
}


Material::~Material()
{
}

void Material::PrepareMaterial(RenderInfo renderInfo, Transform& transform)
{
	//"world" = 0
	//"view" = 1
	//"projection" = 2
	vertexShader->SetMatrix4x4(0, transform.GetWorldMatrix());
	vertexShader->SetMatrix4x4(1, renderInfo.viewMatrix);
	vertexShader->SetMatrix4x4(2, renderInfo.projectionMatrix);

	//"cameraPosition" = 0
	//"light1" = 1
	//"light2" = 2
	pixelShader->SetFloat3(0, renderInfo.cameraPosition);
	pixelShader->SetData(1, &renderInfo.light1, sizeof(RenderLight));
	pixelShader->SetData(2, &renderInfo.light2, sizeof(RenderLight));

	vertexShader->SetShader(true);
	pixelShader->SetShader(true);
}
