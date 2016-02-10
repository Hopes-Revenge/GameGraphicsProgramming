#pragma once

class Entity;

class Component
{
public:
	const static unsigned __int8 UNINDEXED = 255;
	const static Component EMPTY;
	Component();
	~Component();

	virtual void Init();//This is going to be called the before the first update of the object, still have to decide how to do this
	virtual void Added();
	virtual void Removed();
	virtual void Update();

	inline bool operator==(const Component& other) { return index == other.index && parrentEntity == other.parrentEntity; }
	inline bool operator!=(const Component& other) { return !(*this == other); }

	void SetEntiy(Entity* newParrentEntity);
	void SetIndex(unsigned __int8 newIndex) { index = newIndex; }
	Entity* GetEntity() { return parrentEntity; }
	unsigned __int8 GetIndex() { return index; }
	bool GetHasBeenInialized() const { return hasBeenInialized; }
private:
	Entity* parrentEntity;
	//Index is limited to [0, 254] if you want more components than that too bad
	unsigned __int8 index;
	bool hasBeenInialized;
};

