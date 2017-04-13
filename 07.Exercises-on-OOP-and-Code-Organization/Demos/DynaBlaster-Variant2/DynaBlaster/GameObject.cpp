#include "GameObject.h"

GameObject::GameObject(Vector2D position) :
	position(position)
{
}

GameObject::GameObject(Vector2D position, GameObjectPtr owner) :
	position(position),
	owner(owner)
{
}

bool GameObject::hasType(std::string type) const
{
	return this->getType().find(type) != std::string::npos;
}

GameObject::~GameObject()
{
}

Vector2D GameObject::getPosition() const
{
	return this->position;
}

Vector2D GameObject::setPosition(Vector2D position)
{
	return this->position = position;
}

GameObjectPtr GameObject::getOwner() const
{
	return this->owner;
}

void GameObject::handleOwnedObjectDestroyed(GameObjectPtrConst o)
{
}
