#ifndef ENGINE_SHOT_H_
#define ENGINE_SHOT_H_

#include "Moveable.h"

namespace engine
{

	class Shot : public engine::Moveable
	{
	public:
		static Shot* createInstance(Window*, std::string, SDL_Point, SDL_Rect, SDL_Rect highRes, unsigned int mass, float speed, int life, bool enemy, float ySpeedTemp = 0);
		static Shot* createInstance(Window*, std::string, SDL_Point, SDL_Rect, unsigned int mass, float speed, int life, bool enemy, float ySpeedTemp = 0);

		virtual void move(SDL_Window*);
		virtual void actOnCollision(Moveable*);
		bool noLongerInWindow(SDL_Window*) const;
		virtual ~Shot();
	protected:
		Shot(Window*, std::string, SDL_Point, SDL_Rect, unsigned int mass, float speed, int life, float ySpeedTemp = 0);
		Shot(Window*, std::string, SDL_Point, SDL_Rect, SDL_Rect, unsigned int mass, float speed, int life, float ySpeedTemp = 0);
	};

}

#endif
