#pragma once

#include "GameObject.h"
#include "PositionedObjects.h"
#include "Player.h"

class GameState
{
	PositionedObjects objects;
public:
	const int MaxX;
	const int MaxY;

	GameState(int maxX, int maxY, GameObjects objects);

	void setObjects(GameObjects objects);

	const PositionedObjects& getPositionedObjects() const;

	bool isGameOver();

	static Player* getPlayer(GameObjects objects, int playerNumber);

	~GameState();
};

