#include "Component.h"
#include "Entity.h"

const Component Component::EMPTY = Component();

Component::Component()
{
	parrentEntity = nullptr;
	index = UNINDEXED;
	hasBeenInialized = hasBeenInialized;
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

void Component::SetEntiy(Entity * newParrentEntity)
{
	//Only allowed to set the parrent entity once, this may change in the future.
	if (parrentEntity != nullptr) return;
	parrentEntity = newParrentEntity;
}
