#include "Entity.h"



Entity::Entity()
{
	numComponents = 0;
	lastActiveComponentIndex = -1;
	lastUpdatedComponentIndex = -1;
}


Entity::~Entity()
{
}

void Entity::Update()
{
	for (int u = 0; u <= lastUpdatedComponentIndex; ++u) {
		//TODO: Actually update the component, when we figure that out
	}
}
