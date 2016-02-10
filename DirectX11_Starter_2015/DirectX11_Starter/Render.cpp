#include "Render.h"


Render::Render(ID3D11DeviceContext* newDeviceContext)
{
	deviceContext = newDeviceContext;
	startIndex = 0;
	endIndex = 0;
}


Render::~Render()
{
}

//This isnt the greatest
void Render::AddToRenderQueue(DrawnMesh& drawnMesh)
{
	//We don't want to actually draw something if it has no mesh
	if (drawnMesh.GetMesh() == nullptr) return;
	endIndex += 1;
	if (startIndex == endIndex) {
		renderQueue[startIndex] = drawnMesh;
	} else {
		renderQueue[endIndex] = drawnMesh;
	}
}

void Render::UpdateAndRender()
{
	int index = startIndex;
	while (index != endIndex)
	{
		index = (index + 1) % MAX_NUM_OF_RENDERED_OBJECTS;
		renderQueue[index].
	}
}
