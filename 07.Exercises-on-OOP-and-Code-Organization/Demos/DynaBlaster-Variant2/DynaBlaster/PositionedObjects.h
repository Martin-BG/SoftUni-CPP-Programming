#pragma once

#include <vector>

#include "GameObject.h"

class PositionedObjects
{
	GameObjects objects;
	GameObjectsConst objectsConst;
	std::vector<std::vector<GameObjectsConst>> objectsAtPositions;
public:
	PositionedObjects(GameObjects allObjects);

	const GameObjects& getObjects() const;
	const GameObjectsConst& getObjectsConst() const;
	const GameObjectsConst getObjectsAt(const Vector2D &position) const;
};

