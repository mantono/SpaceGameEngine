#include "DialogWindow.h"
#include <iostream>


namespace engine
{

	DialogWindow::DialogWindow(Window* windowPtr, std::string title, int width, int height, double x, int y)
		:addName(false), texture(nullptr), inputText("")
	{
		window = windowPtr;
		nameWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width / x, height / y, SDL_WINDOW_SHOWN);
		nameRenderer = SDL_CreateRenderer(nameWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(nameRenderer, 0, 0, 0, 0);
		SDL_RenderPresent(nameRenderer);
		area.w = width / x;
		area.h = height / y;
		checkName();


	}
	DialogWindow* DialogWindow::createInstance(engine::Window* window)
	{
		DialogWindow* dialog = new DialogWindow(window, "Skriv ditt namn: ", window->getWidth(), window->getHeight(), 4.8, 8);
		return dialog;
	}

	void DialogWindow::checkName()
	{
		while (!addName)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
					{
						inputText.pop_back();
						renderText(createNewTexture());

					}
					else if (((event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) && inputText.length() > 0) || event.key.keysym.sym == SDLK_ESCAPE)
					{
						Text::createInstance(window, inputText, 640, 50);
						addName = true;
					}
				}

				else if (event.type == SDL_TEXTINPUT)
				{
					if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
					{
						inputText += event.text.text;
						renderText(createNewTexture());
					}
				}
				else if (event.type == SDL_QUIT)
				{
					addName = true;
				}
			}
		}
	}

	SDL_Renderer* DialogWindow::getNameRenderer()const
	{
		return nameRenderer;
	}

	void DialogWindow::renderText(SDL_Texture* texture)
	{
		
		SDL_RenderClear(getNameRenderer());
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

		if (inputText == ""){
			SDL_RenderCopy(getNameRenderer(), NULL, &rect, &area);
		}
		else
		{

			SDL_RenderCopy(getNameRenderer(), texture, &rect, &area);
		}
		SDL_RenderPresent(getNameRenderer());
	}

	SDL_Texture* DialogWindow::createNewTexture()
	{
		color = { 255, 255, 255, 255 };
		font = TTF_OpenFont("../engine/fonts/unispace.ttf", 20);
		if(font == nullptr)
		{
			std::cout << TTF_GetError() << std::endl;
			return NULL;
		}

		SDL_Surface *textSurface = TTF_RenderText_Solid(font, inputText.c_str(), color);
		if(textSurface == nullptr)
		{
			std::cerr << SDL_GetError() << std::endl;
			return NULL;
		}
		else
		{ 
			if (texture != nullptr)
			{
				SDL_DestroyTexture(texture);
				texture = nullptr;
			}
			texture = SDL_CreateTextureFromSurface(getNameRenderer(), textSurface);
			if (texture == nullptr)
				std::cerr << SDL_GetError() << std::endl;
			SDL_FreeSurface(textSurface);
			textSurface = nullptr;
		}

		return texture;
	}

	DialogWindow::~DialogWindow()
	{
		if (nameWindow != nullptr)
			SDL_DestroyWindow(nameWindow);
		if (nameRenderer != nullptr)
			SDL_DestroyRenderer(nameRenderer);
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
		if (font != nullptr)
			TTF_CloseFont(font);
	}

}

