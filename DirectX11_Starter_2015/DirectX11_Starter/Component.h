#pragma once

class Entity;
class Transform;

class Component
{
public:
	const static Component EMPTY;
	Component();
	Component(const Component & other);
	Component & operator=(const Component & other);
	~Component();

	virtual void Update();

	void SetEntiy(Entity* newParrentEntity);
	Entity* GetEntity() { return parrentEntity; }
	bool GetHasBeenInialized() const { return hasBeenInialized; }
	Transform* GetTransform();
private:
	Entity* parrentEntity;
	bool hasBeenInialized;
};

