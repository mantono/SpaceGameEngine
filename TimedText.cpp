#include "TimedText.h"
#include "Window.h"
#include <iostream>


namespace engine
{
	TimedText::TimedText(Window* window, std::string input, int x, int y, double time)
	:Text(window, input, x, y), startTime(SDL_GetTicks()), endTime(SDL_GetTicks()+(time*1000)),
	 font(nullptr), text(input), fontPath(window->getDefaultFont()), color(window->getDefaultFontColor()),
	 fontTexture(nullptr), fontSize(window->getDefaultFontSize())
	{}
	
	
	TimedText* TimedText::createInstance(Window* window, std::string input, int x, int y, double time)
	{
		TimedText* textSprite = new TimedText(window, input, x, y,time);
		window->addTimedText(textSprite);
		return textSprite;
	}

	bool TimedText::isTimeOut()
	{
		if (SDL_GetTicks() > endTime)
			return true;		
		else			
			return false;
		
	}

	TimedText::~TimedText()
	{
		if(fontTexture != nullptr)
			SDL_DestroyTexture(fontTexture);
		if (font != nullptr)
			TTF_CloseFont(font);
	}
}
