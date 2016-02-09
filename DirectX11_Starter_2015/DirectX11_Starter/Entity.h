#pragma once
#include "DirectXGameCore.h"
#include "Component.h"
#include "Transform.h"

#define SetComponentIndex(index,component) components[index] = component; component.SetIndex(index);

class Entity
{
public:
	const static int MAX_NUM_COMPONENTS = 5;
	Entity();
	~Entity();

	void AddComponent(Component &newComponent);
	void RemoveComponent(Component &removedComponent);
	void Update();

	int GetNumberOfComponents() { return numComponents; }
	int GetNumberOfUpdatedComponents() { return lastUpdatedComponentIndex + 1; }
	Transform* const GetTransform() { return transform; }
private:
	Transform* transform;
	Component* components = new Component[MAX_NUM_COMPONENTS];
	//Number of components that we have actually created [0, MAX_NUM_COMPONENTS)
	int numComponents;
	//Last index of the component that is enabled, all components after this are enabled also, all components after are disabled. [0, numComponents]
	int lastUpdatedComponentIndex;
};

