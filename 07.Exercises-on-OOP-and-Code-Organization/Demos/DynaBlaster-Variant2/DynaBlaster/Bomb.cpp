#include "Bomb.h"
#include "Flame.h"
#include "Utils.h"

Bomb::Bomb(Vector2D position, int range, GameObjectPtr owner) :
	Destroyable(position, owner),
	range(range)
{
}

GameObjects Bomb::update(const PositionedObjects & allObjects)
{
	if (!this->enteredWorld) 
	{
		this->enteredWorld = true;
		this->timerStart = clock();
		return GameObjects();
	}
	else 
	{
		if (clock() - this->timerStart >= Bomb::BombTimerTicks) {
			return this->destroy(allObjects);
		}
		else {
			return GameObjects();
		}
	}
}

std::string Bomb::getType() const
{
	return "bomb";
}

bool Bomb::isDestroyedOnContactWith(GameObjectPtrConst object) const
{
	return object->hasType("fire");
}

GameObjects Bomb::destroy(const PositionedObjects & allObjects)
{
	Destroyable::destroy(allObjects);

	GameObjects produced;

	Utils::insert(produced, this->produceFlames(Vector2D(0, 1), allObjects));
	Utils::insert(produced, this->produceFlames(Vector2D(1, 0), allObjects));
	Utils::insert(produced, this->produceFlames(Vector2D(0, -1), allObjects));
	Utils::insert(produced, this->produceFlames(Vector2D(-1, 0), allObjects));

	return produced;
}

GameObjects Bomb::produceFlames(Vector2D directionStep, const PositionedObjects & allObjects)
{
	GameObjects flames;

	for (int i = 1; i <= this->range; i++) {
		Vector2D flamePosition = this->getPosition() + (directionStep * i);

		bool canPlaceFlame = true;
		bool canContinue = true;
		GameObjectsConst objectsAtFlamePosition = allObjects.getObjectsAt(flamePosition);
		if (!objectsAtFlamePosition.empty()) 
		{
			for (GameObjectPtrConst o : objectsAtFlamePosition) 
			{
				if (o->hasType("concrete")) 
				{
					canPlaceFlame = false;
				}

				if (o->hasType("concrete") || o->hasType("bomb") || o->hasType("brick")) 
				{
					canContinue = false;
				}
			}
		}

		if (canPlaceFlame) 
		{
			flames.push_back(new Flame(flamePosition));
		}

		if (!canContinue) 
		{
			break;
		}
	}

	return flames;
}
