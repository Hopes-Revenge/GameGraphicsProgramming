#include "Entity.h"



Entity::Entity()
{
	numComponents = 0;
	lastUpdatedComponentIndex = -1;
	for (int c = 0; c < MAX_NUM_COMPONENTS; ++c) {
		components[c] = Component::EMPTY;//Just to be sure;
	}
	transform = new Transform();
}


Entity::~Entity()
{
	for (int c = 0; c < MAX_NUM_COMPONENTS; ++c) {
		components[c].Removed();
	}
	delete[] components;
	delete transform;
}

void Entity::AddComponent(Component &newComponent)
{
	//Right now we always add the component to be updated, this will change in the future

	//if (newComponent == nullptr) return;
	//If we are at max capacity return
	if (numComponents + 1 >= MAX_NUM_COMPONENTS) return;
	//If the component already has an entity we don't want to add it, it already has an owner
	if (newComponent.GetEntity() == nullptr) {
		newComponent.SetEntiy(this);
		//All the components are active so we just add this one to the end
		if (numComponents == lastUpdatedComponentIndex + 1) {
			SetComponentIndex(numComponents, newComponent);
			lastUpdatedComponentIndex = numComponents;
		} else {
			//So we have this component equal the last active plus one and set the old active plus one equal to the numcomponents slot
			lastUpdatedComponentIndex += 1;
			Component temp = components[lastUpdatedComponentIndex];//Okay I am doing swapping slow here, this might get changed in the future
			SetComponentIndex(lastUpdatedComponentIndex, newComponent);
			SetComponentIndex(numComponents, temp);
		}
		newComponent.Added();
		numComponents += 1;
	}

	//Note: don't know if I want to do asserts.
	//static_assert(GetNumberOfComponents() >= MAX_NUM_COMPONENTS, "Tring to add more components than the capacity of components to hold.");
	//static_assert(newComponent, "Trying to add a class that is not a component.");
}

void Entity::RemoveComponent(Component &removedComponent)
{
	//This component is unindexed we, dont care about it then. If the components entity doesn't match this one we dont care about it either
	if (removedComponent.GetIndex() == Component::UNINDEXED || removedComponent.GetEntity() != this) return;
	removedComponent.Removed();
	//Its the last component easiest case
	if (removedComponent.GetIndex() == numComponents - 1) {
		components[removedComponent.GetIndex()] = Component::EMPTY;//We use the "Unsafe version" here
	} else if (removedComponent.GetIndex() <= lastUpdatedComponentIndex) {
		SetComponentIndex(removedComponent.GetIndex(), components[lastUpdatedComponentIndex]);
		SetComponentIndex(lastUpdatedComponentIndex, components[lastUpdatedComponentIndex + 1]);
		lastUpdatedComponentIndex -= 1;
	} else if (removedComponent.GetIndex() < numComponents) {
		SetComponentIndex(removedComponent.GetIndex(), components[numComponents - 1]);
		components[numComponents - 1] = Component::EMPTY;//We use the "Unsafe version" here
	}
	numComponents -= 1;
}



void Entity::Update()
{
	for (int u = 0; u <= lastUpdatedComponentIndex; ++u) {
		components[u].Update();
	}
}
