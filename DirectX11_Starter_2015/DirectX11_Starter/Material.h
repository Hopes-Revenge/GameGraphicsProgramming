#pragma once
#include "SimpleShader.h"

#include "Transform.h"

struct RenderInfo;

class Material
{
public:
	Material(SimpleVertexShader* newVertexShader, SimplePixelShader* newPixelShader, ID3D11ShaderResourceView* newShaderResourceView, ID3D11SamplerState* newSamplerState);
	~Material();

	void SetVertexShader(SimpleVertexShader* newVertexShader) { vertexShader = newVertexShader;  }
	void SetPixelShader(SimplePixelShader* newPixelShader) { pixelShader = newPixelShader; }
	void SetShaderResourceView(ID3D11ShaderResourceView* newShaderResourceView) { shaderResourceView = newShaderResourceView;  }
	void SetSamplerState(ID3D11SamplerState* newSamplerState) { samplerState = newSamplerState; }
	void PrepareMaterial(RenderInfo& renderInfo, Transform& transform);
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	//Stuff for textures
	ID3D11ShaderResourceView* shaderResourceView;//Texture
	ID3D11SamplerState* samplerState;//Sampler
};

