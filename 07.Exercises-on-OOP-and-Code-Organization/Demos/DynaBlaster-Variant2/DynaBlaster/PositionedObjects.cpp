#include <array>
#include "PositionedObjects.h"
#include "Utils.h"

PositionedObjects::PositionedObjects(GameObjects allObjects) :
	objects(allObjects),
	objectsConst(Utils::toConst(allObjects))
{
	int maxX = 0;
	int maxY = 0;

	for (int i = 0; i < allObjects.size(); i++) 
	{
		if (allObjects[i]->getPosition().x > maxX) 
		{
			maxX = allObjects[i]->getPosition().x;
		}

		if (allObjects[i]->getPosition().y > maxY)
		{
			maxY = allObjects[i]->getPosition().y;
		}
	}

	this->objectsAtPositions.clear();
	objectsAtPositions.resize(maxX + 1);
	for (int i = 0; i < objectsAtPositions.size(); i++)
	{
		objectsAtPositions[i].resize(maxY + 1);
	}

	for (GameObjectPtrConst o : this->objects)
	{
		objectsAtPositions[o->getPosition().x][o->getPosition().y].push_back(o);
	}
}

const GameObjects& PositionedObjects::getObjects() const
{
	return this->objects;
}

const GameObjectsConst& PositionedObjects::getObjectsConst() const
{
	return this->objectsConst;
}

const GameObjectsConst PositionedObjects::getObjectsAt(const Vector2D & position) const
{
	if (position.x >= this->objectsAtPositions.size()
		|| position.y >= this->objectsAtPositions[position.x].size()) 
	{
		return GameObjectsConst();
	}

	return this->objectsAtPositions[position.x][position.y];
}
