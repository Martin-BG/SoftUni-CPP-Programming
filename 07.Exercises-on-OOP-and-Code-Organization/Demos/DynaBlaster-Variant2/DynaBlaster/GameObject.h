#pragma once

#include <vector>
#include <string>

#include "Vector2D.h"

class GameObject;

typedef GameObject * GameObjectPtr;
typedef const GameObject * GameObjectPtrConst;
typedef std::vector<GameObjectPtr> GameObjects;
typedef std::vector<GameObjectPtrConst> GameObjectsConst;

class PositionedObjects;

class GameObject
{
	Vector2D position;
	GameObjectPtr owner = nullptr;
public:
	GameObject(Vector2D position);
	GameObject(Vector2D position, GameObjectPtr owner);

	virtual bool isInWorld() const = 0;

	virtual GameObjects update(const PositionedObjects & allObjects) = 0;
	bool hasType(std::string type) const;

	virtual ~GameObject();

	Vector2D getPosition() const;
	Vector2D setPosition(Vector2D position);

	GameObjectPtr getOwner() const;
	virtual void handleOwnedObjectDestroyed(GameObjectPtrConst o);
protected:
	virtual std::string getType() const = 0;
};

