#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include <ctime>

#include "Destroyable.h"

class Bomb : public Destroyable
{
	static const long long BombTimerTicks = 5 * CLOCKS_PER_SEC;

	int range;
	bool enteredWorld;
	clock_t timerStart;

public:
	Bomb(Vector2D position, int range, GameObjectPtr owner);
	
	virtual GameObjects update(const PositionedObjects & allObjects) override;

	virtual std::string getType() const override;

	virtual bool isDestroyedOnContactWith(GameObjectPtrConst object) const override;

	virtual GameObjects destroy(const PositionedObjects & allObjects) override;
private:
	virtual GameObjects produceFlames(Vector2D directionStep, const PositionedObjects & allObjects);
};

