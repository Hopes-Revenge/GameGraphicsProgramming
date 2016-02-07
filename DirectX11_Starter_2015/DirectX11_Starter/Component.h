#pragma once

class Entity;

class Component
{
public:
	Component();
	~Component();

	void SetEntiy(Entity* newParrentEntity);
	Entity* GetEntity() { return parrentEntity; }
private:
	Entity* parrentEntity;
};

