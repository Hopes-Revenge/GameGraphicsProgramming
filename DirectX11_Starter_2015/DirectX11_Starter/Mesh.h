#pragma once
#include "Vertex.h"
#include "DirectXGameCore.h"
#include <d3d11.h>

class Mesh
{
public:
	Mesh(Vertex* vertices, int numVerts, UINT* indices, int newNumIndices, ID3D11Device* device);
	Mesh(char* filename, ID3D11Device* device);
	~Mesh();

	ID3D11Buffer* const* GetVertexBuffer() { return &vertexBuffer;  }
	ID3D11Buffer* GetIndexBuffer() const { return indexBuffer; }
	int GetNumberOfIndices() { return numIndices; }
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numIndices;
};

