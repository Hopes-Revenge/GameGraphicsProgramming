#include "Transform.h"



Transform::Transform()
{
	isDirty = true;
	parrent = nullptr;
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
}

void Transform::RecalculateWorldMatrix()
{
	if (!isDirty) return;//Dont know if I want to keep it.
	isDirty = false;
	//DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(position);
}
