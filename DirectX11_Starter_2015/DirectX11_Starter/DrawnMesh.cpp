#include "DrawnMesh.h"



DrawnMesh::DrawnMesh(Mesh* mesh, ID3D11DeviceContext* deviceContext)
{
	this->mesh = mesh;
	this->deviceContext = deviceContext;
}


DrawnMesh::~DrawnMesh()
{
	//Don't delete the mesh, the mesh will handle itself
}

void DrawnMesh::SetBuffers()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer(), &stride, &offset);
	deviceContext->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void DrawnMesh::DrawIndices()
{
	deviceContext->DrawIndexed(mesh->GetNumberOfIndices(), 0, 0);
}

void DrawnMesh::Draw()
{
	//This is more temporary
	SetBuffers();
	DrawIndices();
}
