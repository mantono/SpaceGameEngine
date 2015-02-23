#include "Text.h"
#include "Window.h"
#include <iostream>
#include <string>

namespace engine
{
	Text::Text(Window* window, std::string input, int x, int y)
	:Static(window, x, y, 100, 100),
	text(input), fontPath(window->getDefaultFont()),
	color(window->getDefaultFontColor()), font(nullptr), fontTexture(nullptr),
	fontSize(window->getDefaultFontSize())
	{
		setFont(window->getDefaultFont());
		createNewTexture();
		updateTexture(fontTexture);
	}

	Text* Text::createInstance(Window* window, std::string input, int x, int y)
	{

		Text* textSprite = new Text(window, input, x, y);
		window->addStatic(textSprite);
		return textSprite;
	}

	void Text::createNewTexture()
	{
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (textSurface == nullptr)
			std::cerr << "Error, could not create new text surface" << std::endl;
		else
		{
			if(fontTexture != nullptr)
			{
				SDL_DestroyTexture(fontTexture);
				fontTexture = nullptr;
			}

			fontTexture = Sprite::createTexture(textSurface);
			if (fontTexture == nullptr)
				std::cerr << "ERROR texture" << std::endl;
		}

		SDL_FreeSurface(textSurface);

		signed int result = SDL_QueryTexture(fontTexture, NULL, NULL, &area.w, &area.h);
		if(result != 0)
			std::cerr << SDL_GetError() << std::endl;
	}


	void Text::setFont(std::string fontPath)
	{
		if(font != nullptr)
		{
			TTF_CloseFont(font);
			font = nullptr;
		}
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if(font == nullptr)
		{
			std::cerr << TTF_GetError() << std::endl;
			return;
		}
		createNewTexture();
		updateTexture(fontTexture);
	}

	void Text::setFontSize(signed short size)
	{
		fontSize = size;
		setFont(fontPath);
	}

	void Text::setText(std::string newText)
	{
		text = newText;
		setFont(fontPath);
	}

	void Text::setText(int intText)
	{
		setText(std::to_string(intText));
	}

	void Text::setText(float floatText)
	{
		setText(std::to_string((int) floatText));
	}

	void Text::setText(double doubleText)
	{
		setText(std::to_string((int) doubleText));
	}

	std::string Text::getText() const
	{
		return text;
	}

	void Text::setColor(SDL_Color& newColor)
	{
		color = newColor;
		setFont(fontPath);
	}


	Text::~Text()
	{
		SDL_DestroyTexture(fontTexture);
		fontTexture = nullptr;
		if(font != nullptr)
			TTF_CloseFont(font);
	}
}
