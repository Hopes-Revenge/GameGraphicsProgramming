#pragma once
#include "Transform.h"
#include "DrawnMesh.h"
#include "SimpleShader.h"
#include <d3d11.h>

struct RenderInfo {
	ID3D11DeviceContext* deviceContext;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	//Temp stuff till materials are in
	SimpleVertexShader* vertexShader;
};

class Render
{
public:
	const static int MAX_NUM_OF_RENDERED_OBJECTS = 100;//Very likely to changed

	Render(ID3D11DeviceContext* newDeviceContext);
	~Render();

	void AddToRenderList(DrawnMesh& drawnMesh);
	void UpdateAndRender(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, SimpleVertexShader* vertShader);//These are probably not going to be passed in latter
private:
	ID3D11DeviceContext* deviceContext;
	DrawnMesh* renderList[MAX_NUM_OF_RENDERED_OBJECTS];
	int endIndex;
};

