#pragma once

class Entity;

class Component
{
public:
	const static unsigned __int8 UNINDEXED = 255;
	const static Component EMPTY;
	Component();
	~Component();

	virtual void Added();
	virtual void Removed();
	virtual void Update();

	inline bool operator==(const Component& other) { return index == other.index && parrentEntity == other.parrentEntity; }
	inline bool operator!=(const Component& other) { return !(*this == other); }

	void SetEntiy(Entity* newParrentEntity);
	void SetIndex(unsigned __int8 newIndex) { index = newIndex; }
	Entity* GetEntity() { return parrentEntity; }
	unsigned __int8 GetIndex() { return index; }
private:
	Entity* parrentEntity;
	unsigned __int8 index;
};

