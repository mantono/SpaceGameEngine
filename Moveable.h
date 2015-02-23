#ifndef ENGINE_MOVEABLE_H_
#define ENGINE_MOVEABLE_H_

#include <SDL.h>
#include "Sprite.h"
#include "Compare.h"
#include <set>
#include <vector>

namespace engine
{

	class Moveable: public Sprite
	{
	public:
		Moveable(Window*, std::string, signed int, signed int, int, int, unsigned int, bool = false);
		virtual void move(SDL_Window*) = 0;
		virtual void actOnCollision(Moveable*) = 0;
		virtual bool noLongerInWindow(SDL_Window*) const;
		bool collision(const Moveable*, SDL_Window*) const;
		float getLife() const;
		virtual bool isAlive() const;
		float getHeading() const;
		unsigned int getPixel(SDL_Surface*, signed int, signed int) const;
		unsigned short getAlpha(SDL_Surface*, signed int, signed int) const;
		unsigned int getMass() const;
		bool checkForPixelCollision() const;
		float getSpeedX() const;
		float getSpeedY() const;
		void takeDamage(float);
		virtual ~Moveable();
	protected:
		std::vector<SDL_Point>  intersectionHasPixelCollision(SDL_Rect&, const Sprite*) const;
		int getWindowWidth(SDL_Window*) const;
		int getWindowHeight(SDL_Window*) const;
		void honorHorizontalBorders(SDL_Window*);
		void honorVerticalBorders(SDL_Window*);
		bool equals(SDL_Point& p1, SDL_Point& p2) const;
		float xSpeed, ySpeed, xCoord, yCoord;
		bool checkPixelCollision;
		float life;
		unsigned int mass;
	};

}

#endif
