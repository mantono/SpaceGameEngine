#ifndef ENGINE_NPC_H_
#define ENGINE_NPC_H_

#include "Sprite.h"
#include "Moveable.h"

namespace engine
{

	class NPC: public engine::Moveable
	{
	public:
		virtual void move(SDL_Window*) = 0;
		double getSeconds() const;
		signed int getRandomInt(unsigned int range);
		virtual ~NPC();
	protected:
		NPC(Window*, std::string, double, signed int, signed int, int = 32, int = 32);
		unsigned short distanceToTopBorder(unsigned short) const;
		unsigned short distanceToBottomBorder(unsigned short) const;
	private:
		const double seconds;
		static unsigned int randCounter;
	};

}

#endif
