#include "FontManager.h"
#include <iostream>

namespace engine
{

	FontManager::FontManager():
	defaultFontPath("../engine/fonts/unispace.ttf"), defaultFontSize(16), defaultFontColor({ 255, 0, 0, 255 })
	{
		if(TTF_Init() != 0)
			std::cout << "Error, could not initialize TTF" << std::endl;
	}


	void FontManager::setDefaultFont(std::string fontPath)
	{
		defaultFontPath = fontPath;
	}

	std::string FontManager::getDefaultFont() const
	{
		return defaultFontPath;
	}

	void FontManager::setDefaultFontSize(signed short size)
	{
		defaultFontSize = size;
	}

	signed short FontManager::getDefaultFontSize() const
	{
		return defaultFontSize;
	}

	void FontManager::setDefaultFontColor(SDL_Color& color)
	{
		defaultFontColor = color;
	}

	SDL_Color FontManager::getDefaultFontColor() const
	{
		return defaultFontColor;
	}


	FontManager::~FontManager()
	{
		TTF_Quit();
	}

}
