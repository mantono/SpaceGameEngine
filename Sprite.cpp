#include "Window.h"
#include "Sprite.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

namespace engine
{
	unsigned int Sprite::sprites = 0;
	unsigned int Sprite::idCounter = 1;

	Sprite::Sprite(Window* window, std::string imagePath, signed int x, signed int y, int width, int height)
	:spriteArea(nullptr), surface(nullptr), renderer(window->getRenderer()), id(idCounter++)
	{
		 if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
			 std::cerr << IMG_GetError() << std::endl;
		surface = IMG_Load(imagePath.c_str());
		if(surface == nullptr)
			std::cerr << "Error, could not load file: " << imagePath << std::endl;

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(texture == nullptr)
			std::cerr << "Error, could not create texture from surface" << std::endl;

		area.x = x;
		area.y = y;
		area.w = width;
		area.h = height;

		sprites++;
	}

	Sprite::Sprite(Window* window, signed int x, signed int y, int width, int height)
	:spriteArea(nullptr), surface(nullptr), renderer(window->getRenderer()), texture(nullptr), id(idCounter++)
	{
		area.x = x;
		area.y = y;
		area.w = width;
		area.h = height;
		sprites++;
	}

	const bool Sprite::operator==(const Sprite& other)
	{
		return id == other.id;
	}

	SDL_Texture* Sprite::createTexture(SDL_Surface* surface)
	{
		return SDL_CreateTextureFromSurface(renderer, surface);
	}

	void Sprite::updateTexture(SDL_Texture* texture)
	{
		if(texture != nullptr)
			this->texture = texture;
	}

	SDL_Texture* Sprite::getTexture() const
	{
		return texture;
	}

	SDL_Surface* Sprite::getSurface() const
	{
		return surface;
	}

	float Sprite::getWidthMultiple() const
	{
		if(spriteArea == nullptr)
			return 1;
		return spriteArea->w / (float)area.w;
	}

	float Sprite::getHeightMultiple() const
	{
		if(spriteArea == nullptr)
			return 1;
		return spriteArea->h / (float)area.h;
	}

	void Sprite::draw()
	{
		SDL_RenderCopy(renderer, texture, spriteArea, &area);
	}

	unsigned int Sprite::getCurrentNumberOfSprites()
	{
		return sprites;
	}

	unsigned int Sprite::getId() const
	{
		return id;
	}

	signed int Sprite::getX() const
	{
		return area.x;
	}

	signed int Sprite::getY() const
	{
		return area.y;
	}

	unsigned int Sprite::getSpriteAreaX() const
	{
		if(spriteArea == nullptr)
			return 0;
		return spriteArea->x;
	}

	unsigned int Sprite::getSpriteAreaY() const
	{
		if(spriteArea == nullptr)
			return 0;
		return spriteArea->y;
	}

	Sprite::~Sprite()
	{
		if(surface != nullptr)
			SDL_FreeSurface(surface);
		if(texture != nullptr)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
		if(spriteArea != nullptr)
		{
			delete spriteArea;
			spriteArea = nullptr;
		}
		sprites--;
	}
}
