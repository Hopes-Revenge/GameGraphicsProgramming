#pragma once
#include "Mesh.h"
#include <d3d11.h>

class DrawnMesh
{
public:
	DrawnMesh(Mesh* mesh, ID3D11DeviceContext* deviceContext);
	~DrawnMesh();

	void SetBuffers();
	void DrawIndices();
	void Draw();
private:
	Mesh* mesh;
	ID3D11DeviceContext* deviceContext;
};

