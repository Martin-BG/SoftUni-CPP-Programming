#pragma once

#include "Vector2D.h"
#include "GameObject.h"
#include "Destroyable.h"

class Player : public Destroyable
{
	int number;
	Vector2D movement;

	bool bombArmed;

	int bombsDropped;
	int bombsAvailable;

	int bombRange;

	bool isAlive;
public:
	Player(int number, Vector2D position);

	int getNumber() const;

	virtual std::string getType() const override;

	virtual bool isDestroyedOnContactWith(GameObjectPtrConst o) const override;

	virtual GameObjects update(const PositionedObjects & allObjects) override;

	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();

	void dropBomb();

	virtual void handleOwnedObjectDestroyed(GameObjectPtrConst o) override;
protected:
	bool canMove(Vector2D position, const PositionedObjects & allObjects) const;
	bool canMoveToObject(GameObjectPtrConst o) const;
};