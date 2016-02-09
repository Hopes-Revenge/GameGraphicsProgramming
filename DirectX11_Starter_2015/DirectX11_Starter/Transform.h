#pragma once
#include <DirectXMath.h>

class Transform
{
public:
	const static Transform NO_PARRENT;
	Transform();
	~Transform();

	//Getter and setters
	void SetPosition(DirectX::XMFLOAT3 newPos);
	void SetRotation(DirectX::XMFLOAT3 newRot);
	void SetScale(DirectX::XMFLOAT3 newScale);
	void SetParrent(Transform* newParrent);
	DirectX::XMFLOAT3 GetPosition() { return position; }
	DirectX::XMFLOAT3 GetRotation() { return rotation; }
	DirectX::XMFLOAT3 GetScale() { return scale; }
	DirectX::XMFLOAT4X4 GetWorldMatrix() { return worldMatrix; }
	Transform* GetParrent() { return parrent; }

	void RecalculateWorldMatrix();
private:
	//we save the world matrix and only recalculate it when this is true, this is set to true when we change information about the transform
	Transform* parrent;
	bool isDirty;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT4X4 worldMatrix;
};

