#include "DrawnMesh.h"
#include "Render.h"


DrawnMesh::DrawnMesh()
{
}

DrawnMesh::DrawnMesh(Render* newRender, Mesh* newMesh)
{
	render = newRender;
	mesh = newMesh;
}


DrawnMesh::~DrawnMesh()
{
	//Don't delete the mesh, the mesh will handle itself
}

void DrawnMesh::Draw(ID3D11DeviceContext * deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer(), &stride, &offset);
	deviceContext->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->DrawIndexed(mesh->GetNumberOfIndices(), 0, 0);
}

void DrawnMesh::Update()
{
	Component::Update();
	if (render == nullptr) return;
	render->AddToRenderQueue(*this);
}
