#ifndef ENGINE_PLAYER_H_
#define ENGINE_PLAYER_H_

#include "EventDriven.h"
#include "Moveable.h"

namespace engine
{

	class Player: public Moveable, public EventDriven
	{
	public:
		void keepInsideWindow(SDL_Window*);
		signed int getScore() const;
		void addScore(signed int);
		virtual ~Player();
	protected:
		Player(Window* , std::string, int, int, int, int, bool = false);
		bool rightKeyPressed, leftKeyPressed, upKeyPressed, downKeyPressed;
	private:
		signed int score;
	};

}

#endif
