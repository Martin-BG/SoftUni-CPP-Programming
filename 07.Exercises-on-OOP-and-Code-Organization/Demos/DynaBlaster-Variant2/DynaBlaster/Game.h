#pragma once

#include "GameObject.h"
#include "GameState.h"

#include "InputReader.h"
#include "OutputWriter.h"

#include "Player.h"

class Game
{
	InputReader * reader;
	OutputWriter * writer;
	GameState state;
	Player * player1;
	Player * player2;
public:
	Game(InputReader * reader, OutputWriter * writer, GameObjects objects, int maxX, int maxY);

	void run();

	void handleInput();
	void update();
	void writeOutput();

	~Game();
};

