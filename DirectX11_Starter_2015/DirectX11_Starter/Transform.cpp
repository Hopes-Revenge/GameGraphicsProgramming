#include "Transform.h"


Transform::Transform()
{
	isDirty = true;
	parrent = nullptr;
	position = DirectX::XMFLOAT3(0, 0, 0);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
	scale = DirectX::XMFLOAT3(1, 1, 1);
	RecalculateWorldMatrix();
}


Transform::~Transform()
{
}

void Transform::SetPosition(DirectX::XMFLOAT3 newPos)
{
	isDirty = true;
	position = newPos;
}

void Transform::SetRotation(DirectX::XMFLOAT3 newRot)
{
	isDirty = true;
	rotation = newRot;
}

void Transform::SetScale(DirectX::XMFLOAT3 newScale)
{
	isDirty = true;
	scale = newScale;
}

void Transform::SetParrent(Transform * newParrent)
{
	//TODO: we need to check to make sure we dont have a circular dependency.
	parrent = newParrent;
}

DirectX::XMFLOAT4X4 Transform::RecalculateWorldMatrix()
{
	if (!isDirty) return worldMatrix;//Dont know if I want to keep it.
	isDirty = false;
	//Okay I would like to change this to try to get rid of the if statement
	if (parrent == nullptr) {
		DirectX::XMMATRIX  calculatedWorldMatrix =
			DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&rotation)) *
			DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));
		DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(calculatedWorldMatrix));
	} else {
		DirectX::XMMATRIX  calculatedWorldMatrix =
			DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&rotation)) *
			DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));
		DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixMultiply(calculatedWorldMatrix, DirectX::XMLoadFloat4x4(&parrent->GetWorldMatrix()))));
	}
	return worldMatrix;
}
