#include "Mesh.h"



Mesh::Mesh(Vertex* vertices, int numVerts, int* indices, int numIndices, ID3D11Device* device)
{
	//Set the indices
	this->numIndices = numIndices;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVerts; 
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	HR(device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer));


	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * numIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	HR(device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer));
}


Mesh::~Mesh()
{
	ReleaseMacro(vertexBuffer);
	ReleaseMacro(indexBuffer);
}
