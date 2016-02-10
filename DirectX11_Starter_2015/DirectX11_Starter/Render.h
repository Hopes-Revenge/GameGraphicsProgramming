#pragma once
#include "Transform.h"
#include "DrawnMesh.h"
#include <d3d11.h>

struct RenderInfo {
	ID3D11DeviceContext* deviceContext;

};

class Render
{
public:
	const static int MAX_NUM_OF_RENDERED_OBJECTS = 100;//Very likely to changed

	Render(ID3D11DeviceContext* newDeviceContext);
	~Render();

	void AddToRenderQueue(DrawnMesh& drawnMesh);
	void UpdateAndRender();
private:
	ID3D11DeviceContext* deviceContext;
	DrawnMesh* renderQueue = new DrawnMesh[MAX_NUM_OF_RENDERED_OBJECTS];
	int startIndex;
	int endIndex;
};

