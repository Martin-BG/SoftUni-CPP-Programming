#include "Player.h"
#include "Bomb.h"
#include "PositionedObjects.h"

Player::Player(int number, Vector2D position) :
	Destroyable(position),
	number(number),
	bombArmed(false),
	bombsDropped(0),
	bombsAvailable(1),
	bombRange(2),
	isAlive(true)
{
}

int Player::getNumber() const
{
	return this->number;
}

std::string Player::getType() const
{
	return "player";
}

bool Player::isDestroyedOnContactWith(GameObjectPtrConst o) const
{
	return o->hasType("flame") || o->hasType("creep");
}

GameObjects Player::update(const PositionedObjects & allObjects)
{
	GameObjects produced = Destroyable::update(allObjects);

	if (this->bombArmed)
	{
		if (allObjects.getObjectsAt(this->getPosition()).size() == 1)
		{
			produced.push_back(new Bomb(this->getPosition(), this->bombRange, this));
			this->bombsDropped++;
		}

		this->bombArmed = false;
	}

	Vector2D targetPosition = this->getPosition() + this->movement;
	if (this->canMove(targetPosition, allObjects))
	{
		this->setPosition(targetPosition);
	}

	// reset movement
	this->movement = Vector2D();

	return produced;
}

void Player::moveUp()
{
	this->movement = Vector2D(0, 1);
}

void Player::moveRight()
{
	this->movement = Vector2D(1, 0);
}

void Player::moveDown()
{
	this->movement = Vector2D(0, -1);
}

void Player::moveLeft()
{
	this->movement = Vector2D(-1, 0);
}

void Player::dropBomb() 
{
	if (this->bombsAvailable > this->bombsDropped) 
	{
		this->bombArmed = true;
	}
}

void Player::handleOwnedObjectDestroyed(GameObjectPtrConst o)
{
	this->bombsDropped--;
}

bool Player::canMove(Vector2D position, const PositionedObjects & allObjects) const
{
	std::vector<std::string> typesCanMoveTo;
	for (GameObjectPtrConst o : allObjects.getObjectsAt(position)) 
	{
		if (!this->canMoveToObject(o)) 
		{
			return false;
		}
	}
	
	return true;
}

bool Player::canMoveToObject(GameObjectPtrConst o) const
{
	return o->hasType("creep") || o->hasType("fire");
}

