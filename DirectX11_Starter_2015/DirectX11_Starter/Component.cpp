#include "Component.h"
#include "Entity.h"

const Component Component::EMPTY = Component();

Component::Component()
{
	parrentEntity = nullptr;
	index = UNINDEXED;
	hasBeenInialized = false;
}

Component::Component(const Component & other)
{
	parrentEntity = other.parrentEntity;
	index = other.index;
	hasBeenInialized = other.hasBeenInialized;
}

Component & Component::operator=(const Component & other)
{
	if (this == &other) return *this;
	parrentEntity = other.parrentEntity;
	index = other.index;
	hasBeenInialized = other.hasBeenInialized;
	return *this;
}


Component::~Component()
{
	//Let the entity handle its own deletion
}

void Component::Init()
{
	hasBeenInialized = true;
}

void Component::Added()
{
}

void Component::Removed()
{
}

void Component::Update()
{
}

void Component::SetEntiy(Entity* newParrentEntity)
{
	//Only allowed to set the parrent entity once, this may change in the future.
	if (parrentEntity != nullptr) return;
	parrentEntity = newParrentEntity;
}

Transform* Component::GetTransform() {
	return parrentEntity->GetTransform();
}
