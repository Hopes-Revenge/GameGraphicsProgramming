#include "Entity.h"



Entity::Entity()
{
	numberOfComponents = 0;
}

Entity::~Entity()
{
	Reset();
}

void Entity::AddComponent(Component* newComponent)
{
	components[numberOfComponents] = newComponent;
	components[numberOfComponents]->SetEntiy(this);
	numberOfComponents++;
}

void Entity::Update()
{
	for (int c = 0; c < numberOfComponents; ++c) {
		components[c]->Update();
	}
}

void Entity::Reset()
{
	numberOfComponents = 0;
	//TODO: reset the transform
	for (int c = 0; c < numberOfComponents; ++c) {
		if (components[c] != nullptr) {
			delete components[c];
			components[c] = nullptr;
		}
	}
}
