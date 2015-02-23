#include "NPC.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace engine
{
	unsigned int NPC::randCounter = 0;

	NPC::NPC(Window* window, std::string imagePath, double seconds, signed int x, signed int y, int width, int height)
	:Moveable(window, imagePath, x, y, width, height, 100), seconds(seconds)
	{
	}

	unsigned short NPC::distanceToTopBorder(unsigned short windowHeight) const
	{
		return windowHeight - (yCoord - area.h);
	}

	unsigned short NPC::distanceToBottomBorder(unsigned short windowHeight) const
	{
		return windowHeight - (yCoord + area.h);
	}

	signed int NPC::getRandomInt(unsigned int range)
	{
		srand(SDL_GetTicks() + getId() * NPC::randCounter++);
		return (rand() % range*2 + 1) - range;
	}

	double NPC::getSeconds() const
	{
		return seconds;
	}

	NPC::~NPC()
	{
	}

}
