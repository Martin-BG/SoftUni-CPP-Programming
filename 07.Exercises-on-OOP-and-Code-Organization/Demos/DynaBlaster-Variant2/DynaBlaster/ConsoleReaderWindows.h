#pragma once

#include <conio.h>

#include "InputReader.h"
class ConsoleReaderWindows :
	public InputReader
{
public:
	virtual bool hasInput() override 
	{
		return _kbhit();
	}

	virtual int readInputCode() override
	{
		return _getch();
	}
};

