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
	vertexShader->SetMatrix4x4("world", transform.GetWorldMatrix());
	vertexShader->SetMatrix4x4("view", renderInfo.viewMatrix);
	vertexShader->SetMatrix4x4("projection", renderInfo.projectionMatrix);
	vertexShader->SetShader(true);
	pixelShader->SetShader(true);
}
