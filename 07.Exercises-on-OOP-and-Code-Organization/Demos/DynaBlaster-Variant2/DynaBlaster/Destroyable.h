#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "PositionedObjects.h"

class Destroyable :
	public GameObject
{
	bool inWorld;
public:
	Destroyable(Vector2D position);
	Destroyable(Vector2D position, GameObjectPtr owner);

	virtual bool isInWorld() const override;

	virtual GameObjects destroy(const PositionedObjects & allObjects);

	virtual GameObjects update(const PositionedObjects & allObjects) override;

	virtual bool isDestroyedOnContactWith(GameObjectPtrConst object) const = 0;

	virtual ~Destroyable() override;
};

