#include "Flame.h"

Flame::Flame(Vector2D position) :
	Destroyable(position)
{
}

std::string Flame::getType() const
{
	return "flame";
}

bool Flame::isDestroyedOnContactWith(GameObjectPtrConst object) const
{
	return false;
}

GameObjects Flame::update(const PositionedObjects & allObjects)
{
	Destroyable::update(allObjects);
	this->destroy(allObjects);

	return GameObjects();
}
