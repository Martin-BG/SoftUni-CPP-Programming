#pragma once
#include "GameState.h"
class OutputWriter
{
public:
	virtual void write(const GameState & state) = 0;

	virtual ~OutputWriter() {
	}
};

