#pragma once
#include "DirectXGameCore.h"
#include "Component.h"
#include "Transform.h"
#include <vector>

class Entity
{
public:
	const static int MAX_NUM_COMPONENTS = 5;
	Entity();
	Entity(const Entity & other);
	Entity& operator=(const Entity& other);
	~Entity();

	void AddComponent(Component* newComponent);
	void Update();

	Transform* const GetTransform() { return transform; }
private:
	Transform* transform;
	std::vector<Component*> components;
};

