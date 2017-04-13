#include <iostream>
#include <vector>
#include <ctime>

#include "Vector2D.h"
#include "GameObject.h"
#include "PositionedObjects.h"

#include "GameState.h"
#include "InputReader.h"
#include "OutputWriter.h"

#include "ConsoleReaderWindows.h"
#include "ConsoleWriterWindows.h"

#include "Player.h"
#include "Game.h"

GameObjects generateObjects() 
{
	GameObjects objects;

	//objects.push_back(new Player(1, Vector2D(1, 40 - 1)));
	//objects.push_back(new Player(2, Vector2D(40 - 1, 1)));

	objects.push_back(new Player(1, Vector2D(10, 10)));
	objects.push_back(new Player(2, Vector2D(15, 15)));

	return objects;
}

InputReader * getInputReader() 
{
	return new ConsoleReaderWindows();
}

OutputWriter * getOutputWriter()
{
	return new ConsoleWriterWindows();
}

int main() 
{
	Game game(getInputReader(), getOutputWriter(), generateObjects(), 40, 40);

	game.run();

	return 0;
}