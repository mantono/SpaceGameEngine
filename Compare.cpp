#include "Compare.h"
#include "NPC.h"
#include "Level.h"

namespace engine
{
	bool Compare::operator()(NPC* first, NPC* second)
	{
		return first->getSeconds() > second->getSeconds();
	}

	bool Compare::operator()(Level* first, Level* second)
	{
		return first->getLevel() > second->getLevel();
	}

	bool Compare::operator()(const SDL_Point& p1, const SDL_Point& p2) const
	{
		if(p1.x != p2.x)
			return p1.x < p2.x;
		return p1.y < p2.y;
	}
}
