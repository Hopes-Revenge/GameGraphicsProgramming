#pragma once
#include "Mesh.h"
#include "Component.h"
#include <d3d11.h>

class Render;

class DrawnMesh : public virtual Component
{
public:
	DrawnMesh();
	DrawnMesh(Render* newRender, Mesh* newMesh);
	~DrawnMesh();

	void Draw(ID3D11DeviceContext* deviceContext);
	void Update();

	Mesh* GetMesh() { return mesh; }
private:
	Render* render;
	Mesh* mesh;
};