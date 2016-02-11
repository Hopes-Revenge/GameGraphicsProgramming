#include "Entity.h"



Entity::Entity()
{
	transform = new Transform();
}

Entity::Entity(const Entity& other)
{
	transform = other.transform;
	components = other.components;
}

Entity & Entity::operator=(const Entity& other)
{
	if (this == &other) return *this;
	for (int c = 0; c < components.size(); ++c) {
		delete components[c];
	}
	delete transform;
	transform = other.transform;
	components = other.components;
	return *this;
}

Entity::~Entity()
{
	for (int c = 0; c < components.size(); ++c) {
		delete components[c];
	}
	delete transform;
}

void Entity::AddComponent(Component * newComponent)
{
	components.push_back(newComponent);
	components[components.size() - 1]->SetEntiy(this);
}

void Entity::Update()
{
	for (int c = 0; c < components.size(); ++c) {
		components[c]->Update();
	}
}
