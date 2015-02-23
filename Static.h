#ifndef ENGINE_STATIC_H_
#define ENGINE_STATIC_H_

#include "Sprite.h"

namespace engine
{

	class Static: public Sprite
	{
	public:
		static Static* createInstance(Window*, std::string, signed int, signed int, int, int);
		static void setBackground(Window*, std::string, int, int);
		virtual ~Static();
	protected:
		Static(Window*, std::string, signed int, signed int, int, int );
		Static(Window*, signed int, signed int, int, int );
	};

}

#endif
