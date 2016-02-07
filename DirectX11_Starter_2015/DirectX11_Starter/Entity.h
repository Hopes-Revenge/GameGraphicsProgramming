#pragma once
#include "DirectXGameCore.h"
#include "Component.h"

class Entity
{
public:
	const static int MAX_NUM_COMPONENTS = 5;
	Entity();
	~Entity();

	template <class T>
	T AddComponent() {
		static_assert(numComponents >= MAX_NUM_COMPONENTS, "Tring to add more components than the capacity of components to hold.");
		T newComponentUncasted();
		Component newComponent = static_cast<Component>(newComponentUncasted);
		static_assert(newComponent == nullptr, "Trying to add a class that is not a component.");
		newComponent.SetEntiy(*this);
		components[numComponents] = newComponent;
		newComponent += 1;
		return newComponent;
	}
	void Update();

	int GetNumberOfComponents() { return numComponents; }
	int GetNumberOfActiveComponents() { return lastActiveComponentIndex + 1; }
	int GetNumberOfUpdatedComponents() { return lastUpdatedComponentIndex + 1; }
private:
	Component components[MAX_NUM_COMPONENTS];
	//Number of components that we have actually created [0, MAX_NUM_COMPONENTS)
	int numComponents;
	//Last index of the component that is enabled, all components after this are enabled also, all components after are disabled. [0, numComponents]
	int lastActiveComponentIndex;
	//Last index of the component which is to be updated, all components before are also updated, all components after are not enabled. [0, lastActiveComponentIndex]
	int lastUpdatedComponentIndex;
};

