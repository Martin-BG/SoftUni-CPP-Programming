#pragma once
#include "Destroyable.h"
class Flame :
	public Destroyable
{
public:
	Flame(Vector2D position);

	virtual std::string getType() const override;

	virtual bool isDestroyedOnContactWith(GameObjectPtrConst object) const override;

	virtual GameObjects update(const PositionedObjects & allObjects) override;
};

