#include "Moveable.h"
#include "Compare.h"
#include <SDL.h>
#include <iostream>

namespace engine
{
	Moveable::Moveable(Window* window, std::string imagePath, signed int x, signed int y, int width, int height, unsigned int mass, bool pixelCollision)
	:Sprite(window, imagePath, x, y, width, height),
	xSpeed(0), ySpeed(0), xCoord(x), yCoord(y),
	checkPixelCollision(pixelCollision), life(100), mass(mass)
	{}

	bool Moveable::noLongerInWindow(SDL_Window* window) const
	{
		return xCoord < - area.w;
	}

	void Moveable::takeDamage(float damage)
	{
		life -= damage;
	}

	bool Moveable::equals(SDL_Point& p1, SDL_Point& p2) const
	{
 		return p1.x == p2.x && p1.y == p2.y;
	}

	bool Moveable::collision(const Moveable* other, SDL_Window* window) const
	{
		if(this == other)
			return false;

		if(!(isAlive() && other->isAlive()))
			return false;

		if(getX() > (signed) getWindowWidth(window) || other->getX() > (signed) getWindowWidth(window))
			return false;

		if(!SDL_HasIntersection(&this->area, &other->area))
		{
			return false;
		}

		if(!(checkPixelCollision||other->checkForPixelCollision()))
			return true;

		SDL_Rect intersection;
		SDL_IntersectRect(&this->area, &other->area, &intersection);

		std::vector<SDL_Point> hitCoordsThis = intersectionHasPixelCollision(intersection, this);

		if(!hitCoordsThis.empty())
		{
			SDL_IntersectRect(&other->area, &this->area, &intersection);
			std::vector<SDL_Point>hitCoordsOther = intersectionHasPixelCollision(intersection, other);

			if(!hitCoordsOther.empty())
			{
				for(SDL_Point point1 : hitCoordsThis)
				{
					for(SDL_Point point2 : hitCoordsOther)
					{
						if(equals(point1, point2))
							return true;
					}
				}
				return false;
			}
		}
		return false;
	}

	std::vector<SDL_Point> Moveable::intersectionHasPixelCollision(SDL_Rect& intersection, const Sprite* sprite) const
	{
		intersection.x -= sprite->getX();
		intersection.y -= sprite->getY();

		SDL_Surface* source = sprite->getSurface();

		const float mX = sprite->getWidthMultiple();
		const float mY = sprite->getHeightMultiple();
		const unsigned char mXincrement = ceil(mX);
		const unsigned char mYincrement = ceil(mY);
		const unsigned short spriteSheetX = sprite->getSpriteAreaX();
		const unsigned short spriteSheetY = sprite->getSpriteAreaY();
		const signed int lastCoordX = (intersection.w + intersection.x)*mX + spriteSheetX;
		const signed int lastCoordY = (intersection.h + intersection.y)*mY + spriteSheetY;

 		std::vector<SDL_Point> hitCoords;

		unsigned short y = intersection.y*mY + spriteSheetY;

		for(; y < lastCoordY; y+=mYincrement)
		{
			unsigned short x = intersection.x*mX + spriteSheetX;
			for(; x < lastCoordX; x+=mXincrement)
			{
				const Uint32 pixel = getPixel(source, x, y);

				Uint8 r, g, b, a;
				SDL_GetRGBA(pixel, source->format, &r, &g, &b, &a);
				unsigned int aInt = (unsigned int) a;

				if(aInt >= 50)
				{
					unsigned short trueX = sprite->getX()+(x-spriteSheetX)/mX;
					unsigned short trueY = sprite->getY()+(y-spriteSheetY)/mY;
					SDL_Point p = {trueX, trueY};
					hitCoords.push_back(p);
				}
			}
		}
		return hitCoords;
	}

	unsigned short Moveable::getAlpha(SDL_Surface* surface, signed int x, signed int y) const
	{
		SDL_LockSurface(surface);
		Uint32 alphaBits;
		const Uint32 *pixels = (Uint32*)surface->pixels;
		const Uint32 pixelData = pixels[y*surface->pitch + x*surface->format->BytesPerPixel];
		alphaBits = pixelData & surface->format->Amask;
		alphaBits >>= surface->format->Ashift;
		alphaBits <<= surface->format->Aloss;
		SDL_UnlockSurface(surface);
		return (Uint8)alphaBits;
	}

	unsigned int Moveable::getPixel(SDL_Surface* surface, signed int x, signed int y) const
	{
		SDL_LockSurface(surface);
		Uint8* pixel = (Uint8 *) surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
		SDL_UnlockSurface(surface);
		return *(Uint32*)pixel;
	}

	int Moveable::getWindowWidth(SDL_Window* window) const
	{
		int width;
		SDL_GetWindowSize(window, &width, NULL);
		return width;
	}

	int Moveable::getWindowHeight(SDL_Window* window) const
	{
		int height;
		SDL_GetWindowSize(window, NULL, &height);
		return height;
	}

	float Moveable::getSpeedX() const
	{
		return xSpeed;
	}

	float Moveable::getSpeedY() const
	{
		return ySpeed;
	}

	float Moveable::getLife() const
	{
		return life;
	}

	bool Moveable::isAlive() const
	{
		return life > 0;
	}

	unsigned int Moveable::getMass() const
	{
		return mass;
	}

	float Moveable::getHeading() const
	{
		return 0;
	}

	bool Moveable::checkForPixelCollision() const
	{
		return checkPixelCollision;
	}

	void Moveable::honorHorizontalBorders(SDL_Window* window)
	{
		int windowHeight = getWindowHeight(window);

		if(yCoord < 0)
		{
			yCoord = 0;
			ySpeed = 0;
		}

		if(yCoord > windowHeight - area.h)
		{
			yCoord = windowHeight - area.h;
			ySpeed = 0;
		}
	}

	void Moveable::honorVerticalBorders(SDL_Window* window)
	{
		int windowWidth = getWindowWidth(window);

		if(xCoord < 0)
		{
			xCoord = 0;
			xSpeed = 0;
		}

		if(xCoord > windowWidth - area.w)
		{
			xCoord = windowWidth - area.w;
			xSpeed = 0;
		}
	}

	Moveable::~Moveable()
	{
	}

}
