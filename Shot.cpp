#include "Shot.h"
#include <SDL.h>
#include <iostream>
#include "Window.h"


namespace engine
{

	Shot::Shot(Window* window, std::string imagePath, SDL_Point coord, SDL_Rect size, unsigned int mass, float speed, int life, float ySpeedTemp)
	:Moveable(window, imagePath, coord.x, coord.y, size.w, size.h, mass, false)
	{
			xSpeed = speed;
			xCoord = coord.x;
			yCoord = coord.y;
			ySpeed = ySpeedTemp;
			life = 1;
	}

	Shot::Shot(Window* window, std::string imagePath, SDL_Point coord, SDL_Rect size, SDL_Rect highRes, unsigned int mass, float speed, int life, float ySpeedTemp)
	:Moveable(window, imagePath, coord.x, coord.y, size.w, size.h, mass, true)
	{
			xSpeed = speed;
			xCoord = coord.x;
			yCoord = coord.y;
			ySpeed = ySpeedTemp;
			life = 1;
			spriteArea = new SDL_Rect{highRes.x, highRes.y, highRes.w, highRes.h};
	}

	Shot* Shot::createInstance(Window* window, std::string imagePath, SDL_Point coord, SDL_Rect size, unsigned int mass, float speed, int life, bool enemy, float ySpeedTemp)
	{
		Shot *s = new Shot(window, imagePath, coord, size, mass, speed, life, ySpeedTemp);
		window->addShot(s);
		return s;
	}

	Shot* Shot::createInstance(Window* window, std::string imagePath, SDL_Point coord, SDL_Rect size, SDL_Rect highRes, unsigned int mass, float speed, int life, bool enemy, float ySpeedTemp)
	{
		Shot *s = new Shot(window, imagePath, coord, size, highRes, mass, speed, life, ySpeedTemp);
		window->addShot(s);
		return s;
	}

	void Shot::move(SDL_Window* window)
	{
		xCoord += xSpeed;
		area.x = round(xCoord);
		yCoord += ySpeed;
		area.y = round(yCoord);

	}

	void Shot::actOnCollision(Moveable*)
	{
		life = 0;
	}

	bool Shot::noLongerInWindow(SDL_Window* window) const
	{
		return xCoord > getWindowWidth(window)|| xCoord < 0;
	}

	Shot::~Shot()
	{
	}

}
