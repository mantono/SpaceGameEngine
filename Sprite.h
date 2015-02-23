#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

namespace engine
{
	class Window;
	class Sprite
	{
	public:
		virtual void draw();
		const bool operator==(const Sprite&);
		signed int getX() const;
		signed int getY() const;
		unsigned int getId() const;
		static unsigned int getCurrentNumberOfSprites();
		SDL_Surface* getSurface() const;
		float getWidthMultiple() const;
		float getHeightMultiple() const;
		unsigned int getSpriteAreaY() const;
		unsigned int getSpriteAreaX() const;
		virtual ~Sprite() = 0;

	protected:
		Sprite(Window*, std::string, signed int, signed int, int, int);
		Sprite(Window*, signed int, signed int, int, int );
		SDL_Texture* createTexture(SDL_Surface*);
		SDL_Texture* getTexture() const;
		void updateTexture(SDL_Texture*);
		SDL_Rect area;
		SDL_Rect *spriteArea;
		SDL_Surface* surface;

	private:
		Sprite();
		Sprite(const Sprite&);
		const Sprite& operator=(const Sprite&);
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		static unsigned int sprites;
		const unsigned int id;
		static unsigned int idCounter;
	};
}

#endif
