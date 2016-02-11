#include "Transform.h"


Transform::Transform()
{
	isDirty = true;
	parrent = nullptr;
	position = DirectX::XMFLOAT3(0, 0, 0);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
	scale = DirectX::XMFLOAT3(1, 1, 1);
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixIdentity());
}

Transform::Transform(const Transform & other)
{
	isDirty = other.isDirty;
	parrent = other.parrent;
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;
	worldMatrix = other.worldMatrix;
}

Transform & Transform::operator=(const Transform & other)
{
	if (this == &other) return *this;
	isDirty = other.isDirty;
	parrent = other.parrent;
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;
	worldMatrix = other.worldMatrix;
	return *this;
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
	//Okay I would like to change this to try to get rid of the if statement
	DirectX::XMMATRIX allignedWorldMatrix = DirectX::XMLoadFloat4x4(&worldMatrix);
	if (parrent == nullptr) {
		if (!isDirty) return worldMatrix;
		DirectX::XMMATRIX  calculatedWorldMatrix =
			DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&rotation)) *//GIMBAL LOCK
			DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));
		DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(calculatedWorldMatrix));
	} else {
		//if (!isDirty || !parrent->isDirty) return worldMatrix;//Dont know if I want to keep it.
		DirectX::XMMATRIX  calculatedWorldMatrix =
			DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&rotation)) *
			DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));
		DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixMultiply(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&parrent->GetWorldMatrix())), calculatedWorldMatrix)));
	}
	isDirty = false;
	return worldMatrix;
}
