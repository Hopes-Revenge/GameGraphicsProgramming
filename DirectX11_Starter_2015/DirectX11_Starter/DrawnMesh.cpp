#include "DrawnMesh.h"
#include "Render.h"
#include "Transform.h"

DrawnMesh::DrawnMesh()
{
	Component::Component();
	render = nullptr;
	mesh = nullptr;
}

DrawnMesh::DrawnMesh(Render* newRender, Mesh* newMesh)
{
	Component::Component();
	render = newRender;
	mesh = newMesh;
}

DrawnMesh::DrawnMesh(const DrawnMesh& other)
{
	Component::Component(other);
	render = other.render;
	mesh = other.mesh;
}

DrawnMesh & DrawnMesh::operator=(const DrawnMesh& other)
{
	Component::operator=(other);
	if (this == &other) return *this;
	render = other.render;
	mesh = other.mesh;
	return *this;
}

DrawnMesh::~DrawnMesh()
{
	//Don't delete the mesh, the mesh will handle itself
}

#include "Entity.h"

//This is just temporary, I still have to figure out how exactly I want to do rendering
void DrawnMesh::Draw(RenderInfo renderInfo)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	Transform* t = GetTransform();

	renderInfo.vertexShader->SetMatrix4x4("world", GetTransform()->GetWorldMatrix());
	renderInfo.vertexShader->SetMatrix4x4("view", renderInfo.viewMatrix);
	renderInfo.vertexShader->SetMatrix4x4("projection", renderInfo.projectionMatrix);
	renderInfo.vertexShader->CopyAllBufferData();

	renderInfo.deviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer(), &stride, &offset);
	renderInfo.deviceContext->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	renderInfo.deviceContext->DrawIndexed(mesh->GetNumberOfIndices(), 0, 0);
}

void DrawnMesh::Update()
{
	Component::Update();
	if (render == nullptr) return;
	render->AddToRenderList(*this);
}
