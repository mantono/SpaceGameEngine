/*
 * Compare.h
 *
 *  Created on: 2 jan 2015
 *      Author: anton
 */

#ifndef ENGINE_COMPARE_H_
#define ENGINE_COMPARE_H_

#include <SDL.h>

namespace engine
{
	class NPC;
	class Level;
	class Compare
	{
	public:
		bool operator()(NPC*, NPC*);
		bool operator()(Level*, Level*);
		bool operator()(const SDL_Point&, const SDL_Point&) const;
	};

}

#endif
