#pragma once
#include "GameObject.h"
#include "Player.h"
#include "OutputWriter.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <Windows.h>

class ConsoleWriterWindows :
	public OutputWriter
{
public:
	virtual void write(const GameState & state) override
	{
		std::vector<std::string> lines;
		for (int row = 0; row < state.MaxY; row++)
		{
			lines.push_back(std::string(state.MaxX, ' '));
		}


		for (GameObjectPtrConst o : state.getPositionedObjects().getObjectsConst()) 
		{
			Vector2D screenPosition(state.MaxY - o->getPosition().y - 1, o->getPosition().x);
			lines[screenPosition.x][screenPosition.y] = getRenderSymbol(o);
		}

		std::ostringstream outputStream;
		for (auto line : lines) 
		{
			outputStream << line << std::endl;
		}

		COORD cur = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

		std::cout << outputStream.str();
	}

	~ConsoleWriterWindows() override
	{
	}
private:
	char getRenderSymbol(GameObjectPtrConst o)
	{
		if (o->hasType("player"))
		{
			return dynamic_cast<const Player*>(o)->getNumber() + '0';
		}

		if (o->hasType("bomb"))
		{
			return '@';
		}

		if (o->hasType("flame"))
		{
			return '*';
		}

		if (o->hasType("ghost"))
		{
			return '&';
		}

		if (o->hasType("blob"))
		{
			return 'O';
		}

		return '?';
	}
};

