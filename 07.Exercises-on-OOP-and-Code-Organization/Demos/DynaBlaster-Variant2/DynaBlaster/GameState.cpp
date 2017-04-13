#include "GameState.h"
#include "Player.h"

GameState::GameState(int maxX, int maxY, GameObjects objects) :
	MaxX(maxX),
	MaxY(maxY),
	objects(objects)
{
}

void GameState::setObjects(GameObjects objects)
{
	this->objects = objects;
}

const PositionedObjects & GameState::getPositionedObjects() const
{
	return this->objects;
}

bool GameState::isGameOver()
{
	return getPlayer(this->objects.getObjects(), 1) == nullptr
		|| getPlayer(this->objects.getObjects(), 2) == nullptr;
}

Player* GameState::getPlayer(GameObjects objects, int playerNumber)
{

	Player * player = nullptr;
	for (GameObjectPtr o : objects)
	{
		if (o->hasType("player"))
		{
			Player * asPlayer = dynamic_cast<Player*>(o);
			if (asPlayer->getNumber() == playerNumber)
			{
				player = asPlayer;
			}
		}
	}

	return player;

}

GameState::~GameState()
{
}
