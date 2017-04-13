#include "Destroyable.h"


Destroyable::~Destroyable()
{
}

Destroyable::Destroyable(Vector2D position) :
	GameObject(position),
	inWorld(true)
{
}

Destroyable::Destroyable(Vector2D position, GameObjectPtr owner) :
	GameObject(position, owner),
	inWorld(true)
{
}

bool Destroyable::isInWorld() const
{
	return this->inWorld;
}

GameObjects Destroyable::destroy(const PositionedObjects & allObjects)
{
	this->inWorld = false;
	return GameObjects();
}

GameObjects Destroyable::update(const PositionedObjects & allObjects)
{
	GameObjects produced;
	for (GameObjectPtrConst o : allObjects.getObjectsAt(this->getPosition()))
	{
		if (this->isDestroyedOnContactWith(o))
		{
			produced = this->destroy(allObjects);
			break;
		}
	}

	return produced;
}
