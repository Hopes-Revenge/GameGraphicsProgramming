#include "Light.h"

GameLight::GameLight()
{
	renderLight.AmbientColor = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1);
	renderLight.DiffuseColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1);
}

GameLight::GameLight(DirectX::XMFLOAT4 newAmbientColor, DirectX::XMFLOAT4 newDiffuseColor)
{
	renderLight.AmbientColor = newAmbientColor;
	renderLight.DiffuseColor = newDiffuseColor;
}

GameLight::~GameLight()
{
}

RenderLight& GameLight::GetRenderLightData()
{
	renderLight.Direction = transform.GetForwardVector();
	return renderLight;
}
