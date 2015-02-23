#include "Level.h"

namespace engine
{

	Level::Level(Window* window, unsigned int level)
	:window(window), level(level)
	{
	}

	unsigned int Level::getLevel()
	{
		return level;
	}

	Level::~Level()
	{
	}

}
