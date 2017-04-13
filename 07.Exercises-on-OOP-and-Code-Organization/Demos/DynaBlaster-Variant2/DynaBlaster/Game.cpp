#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Utils.h"
#include <ctime>

Game::Game(InputReader * reader, OutputWriter * writer, GameObjects objects, int maxX, int maxY) :
	reader(reader),
	writer(writer),
	state(maxX, maxY, objects),
	player1(GameState::getPlayer(objects, 1)),
	player2(GameState::getPlayer(objects, 2))
{
	state.setObjects(objects);
}

void Game::run()
{
	while (!this->state.isGameOver())
	{
		clock_t start = clock();
		this->handleInput();
		this->update();
		this->writeOutput();

		while (clock() - start < 0.2 * CLOCKS_PER_SEC) {
		}
	}
}

void Game::handleInput()
{
	if (this->reader->hasInput())
	{
		char code = this->reader->readInputCode();

		switch (code)
		{
		case 'w': this->player1->moveUp(); break;
		case 'd': this->player1->moveRight(); break;
		case 's': this->player1->moveDown(); break;
		case 'a': this->player1->moveLeft(); break;
		case 'f': this->player1->dropBomb(); break;

		case 'i': this->player2->moveUp(); break;
		case 'l': this->player2->moveRight(); break;
		case 'k': this->player2->moveDown(); break;
		case 'j': this->player2->moveLeft(); break;
		case 'p': this->player2->dropBomb(); break;
		}
	}
}

void Game::update()
{
	GameObjects remainingAfterUpdate;
	GameObjects destroyedAfterUpdate;

	for (GameObjectPtr o : this->state.getPositionedObjects().getObjects())
	{
		GameObjects produced = o->update(this->state.getPositionedObjects());

		if (o->isInWorld())
		{
			remainingAfterUpdate.push_back(o);
		}
		else
		{
			if (o->getOwner() != nullptr)
			{
				o->getOwner()->handleOwnedObjectDestroyed(o);
			}

			destroyedAfterUpdate.push_back(o);
		}

		Utils::insert(remainingAfterUpdate, produced);
	}

	this->state.setObjects(remainingAfterUpdate);

	for (GameObjectPtr o : destroyedAfterUpdate)
	{
		delete o;
	}
}

void Game::writeOutput()
{
	this->writer->write(this->state);
}


Game::~Game()
{
	delete this->reader;
	delete this->writer;
	
	for (GameObjectPtr o : this->state.getPositionedObjects().getObjects())
	{
		delete o;
	}
}
