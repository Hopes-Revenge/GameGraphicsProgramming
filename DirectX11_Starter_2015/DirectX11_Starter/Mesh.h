#pragma once
#include "Vertex.h"
#include "DirectXGameCore.h"
#include <d3d11.h>

class Mesh
{
public:
	Mesh(const char* newName, Vertex* vertices, int numVerts, UINT* indices, int newNumIndices, ID3D11Device* device);
	Mesh(const char* newName, const char* filename, ID3D11Device* device);
	~Mesh();

	ID3D11Buffer* const* GetVertexBuffer() { return &vertexBuffer;  }
	ID3D11Buffer* GetIndexBuffer() const { return indexBuffer; }
	int GetNumberOfIndices() { return numIndices; }
	const char* const GetName() { return name; }
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numIndices;
	const char* name;
};

