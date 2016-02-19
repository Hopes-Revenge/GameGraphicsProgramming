#include "Render.h"


Render::Render(ID3D11DeviceContext* newDeviceContext)
{
	deviceContext = newDeviceContext;
	endIndex = 0;
}


Render::~Render()
{
	
}

//This is probably going to get re written, for one the materials 
//can be sorted so we only have to call view and projection matrix once per unique vertex shader
void Render::AddToRenderList(DrawnMesh& drawnMesh)
{
	//We don't want to actually draw something if it has no mesh
	if (drawnMesh.GetMesh() == nullptr) return;
	if (endIndex + 1 >= MAX_NUM_OF_RENDERED_OBJECTS) return;
	renderList[endIndex] = &drawnMesh;
	endIndex += 1;
}

void Render::UpdateAndRender(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix)
{
	RenderInfo renderInfo = RenderInfo();
	renderInfo.deviceContext = deviceContext;
	renderInfo.viewMatrix = viewMatrix;
	renderInfo.projectionMatrix = projectionMatrix;

	//vertShader->SetMatrix4x4("view", renderInfo.viewMatrix);
	//vertShader->SetMatrix4x4("projection", renderInfo.projectionMatrix);
	for (int r = 0; r < endIndex; r++) {
		renderList[r]->Draw(renderInfo);
	}
	endIndex = 0;
}
