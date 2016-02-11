#include "Component.h"
#include "Entity.h"

const Component Component::EMPTY = Component();

Component::Component()
{
	parrentEntity = nullptr;
	hasBeenInialized = false;
}

Component::Component(const Component & other)
{
	parrentEntity = other.parrentEntity;
	hasBeenInialized = other.hasBeenInialized;
}

Component & Component::operator=(const Component & other)
{
	if (this == &other) return *this;
	parrentEntity = other.parrentEntity;
	hasBeenInialized = other.hasBeenInialized;
	return *this;
}

Component::~Component(){    
	
}

void Component::Update()
{
}

void Component::SetEntiy(Entity* newParrentEntity)
{
	parrentEntity = newParrentEntity;
}

Transform* Component::GetTransform() {
	return parrentEntity->GetTransform();
}
