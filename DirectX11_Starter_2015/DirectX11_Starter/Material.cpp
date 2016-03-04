#include "Material.h"
#include "Render.h"
#include "Logger.h"

Material::Material(SimpleVertexShader* newVertexShader, SimplePixelShader* newPixelShader, ID3D11ShaderResourceView* newShaderResourceView, ID3D11SamplerState* newSamplerState)
{
	vertexShader = newVertexShader;
	pixelShader = newPixelShader;
	shaderResourceView = newShaderResourceView;
	samplerState = newSamplerState;
}


Material::~Material()
{
}

void Material::PrepareMaterial(RenderInfo& renderInfo, Transform& transform)
{
	//"world" = 0
	//"view" = 1
	//"projection" = 2
	vertexShader->SetMatrix4x4(0, transform.GetWorldMatrix());
	if (renderInfo.currentVertexShader != vertexShader) {
		vertexShader->SetMatrix4x4(1, renderInfo.viewMatrix);
		vertexShader->SetMatrix4x4(2, renderInfo.projectionMatrix);
		vertexShader->SetShader(true);
		renderInfo.currentVertexShader = vertexShader;
		//LogText("Swap Vert");
	}
	else {
		vertexShader->CopyBufferData(0);//The world matrix needs to be set per object
	}


	//"cameraPosition" = 0
	//"light1" = 1
	//"light2" = 2

	//diffuseTexture 0
	//samplerState 0
	if (renderInfo.currentPixelShader != pixelShader) {
		//LogText("Swap Pixel");
		pixelShader->SetFloat3(0, renderInfo.cameraPosition);
		pixelShader->SetData(1, &renderInfo.light1, sizeof(RenderLight));
		pixelShader->SetData(2, &renderInfo.light2, sizeof(RenderLight));
		pixelShader->SetShaderResourceView(0, shaderResourceView);
		pixelShader->SetSamplerState(0, samplerState);
		pixelShader->SetShader(true);
		renderInfo.currentPixelShader = pixelShader;
	}
}
