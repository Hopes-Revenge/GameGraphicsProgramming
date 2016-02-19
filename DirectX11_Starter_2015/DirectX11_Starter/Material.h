#pragma once
#include "SimpleShader.h"

#include "Transform.h"

struct RenderInfo;

class Material
{
public:
	Material(SimpleVertexShader* newVertexShader, SimplePixelShader* newPixelShader);
	~Material();

	void SetVertexShader(SimpleVertexShader* newVertexShader) { vertexShader = newVertexShader;  }
	void SetVertexShader(SimplePixelShader* newPixelShader) { pixelShader = newPixelShader; }
	void PrepareMaterial(RenderInfo renderInfo, Transform& transform);
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};

