#include "Component.h"



Component::Component()
{
	parrentEntity = nullptr;
}


Component::~Component()
{
	//Let the entity handle its own deletion
}

void Component::SetEntiy(Entity * newParrentEntity)
{
	//Only allowed to set the parrent entity once, this may change in the future.
	if (parrentEntity != nullptr) return;
	parrentEntity = newParrentEntity;
}
