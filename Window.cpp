#include "Window.h"
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>
#include <iostream>



namespace engine
{

	Window::Window(std::string title, unsigned int width, unsigned int height)
		:keepRunning(true), fps(100), loopCounter(0), timeSinceRedraw(0), lastLoopTicks(0), windowWidth(width), windowHeight(height),
		timePaused(0), player(nullptr), background(nullptr), fontManager(new FontManager()), currentLevel(nullptr)

	{
		if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
			std::cout << SDL_GetError() << std::endl;
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
			std::cout << "Error, could not create renderer" << std::endl;
	}

	void Window::deleteRemainingSprites()
	{
		while (!npcQueue.empty())
		{
			delete npcQueue.top();
			npcQueue.pop();
		}
		if (background != nullptr)
			delete background;
		for (Sprite* sprite : staticSprites)
			delete sprite;
		for (Moveable* sprite : npcSprites)
			delete sprite;
		for (Moveable* sprite : playerSprites)
			delete sprite;
		for (Sprite* sprite : timedTextSprites)
			delete sprite;
	}

	void Window::deleteRemainingLevels()
	{
		while (!levels.empty())
		{
			delete levels.top();
			levels.pop();
		}

		if (currentLevel != nullptr)
			delete currentLevel;

	}

	void Window::bindKey(int key, std::function<void(void)> fnc)
	{
		bindings.push_back(KeyBinding::getInstance(key, fnc));

	}

	Window::~Window()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		deleteRemainingSprites();
		deleteRemainingLevels();
		delete fontManager;
		IMG_Quit();

		signed int sprites = engine::Sprite::getCurrentNumberOfSprites();
		if (sprites != 0)
			std::cout << "Warning! You still have " << sprites << " sprites allocated in memory" << std::endl;
		for (KeyBinding* kb : bindings){
			delete kb;
		}
	}

	void Window::addStatic(Static* sprite)
	{
		staticSprites.push_back(sprite);
	}

	void Window::addTimedText(TimedText* text)
	{
		timedTextSprites.push_back(text);
	}

	void Window::addShot(Shot* shot)
	{
		if(shot->getSpeedX() < 0)
			npcSprites.push_back(shot);
		else
			playerSprites.push_back(shot);

	}

	void Window::addPlayer(Player* player)
	{
		this->player = player;
		playerSprites.push_back(player);
		addEventDriven(player);
	}

	void Window::addNPC(NPC* npc)
	{
		npcQueue.push(npc);
	}

	void Window::addEventDriven(EventDriven* sprite)
	{
		eventDrivenSprites.push_back(sprite);
	}

	void Window::setBackground(Static* newBackground)
	{
		if (background != nullptr)
			delete background;
		background = newBackground;
	}

	void Window::addLevel(Level* level)
	{
		levels.push(level);
	}

	bool Window::loadNextLevel()
	{
		if (currentLevel != nullptr)
		{
			currentLevel->after();
			delete currentLevel;
			currentLevel = nullptr;
		}
		if (levels.empty())
			return false;
		currentLevel = levels.top();
		levels.pop();
		currentLevel->load();
		timePaused = SDL_GetTicks();
		return true;
	}

	void Window::pollNPC()
	{
		if (npcQueue.empty())
			return;
		if (npcQueue.top()->getSeconds() * 1000 <= (SDL_GetTicks() - timePaused))
		{
			npcSprites.push_back(npcQueue.top());
			npcQueue.pop();
		}
	}

	unsigned int Window::pause()
	{
		unsigned int timePauseStarted = SDL_GetTicks();
		while (keepRunning)
		{
			while (!SDL_PollEvent(&event))
				SDL_Delay(100);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				keepRunning = false;
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_PAUSE)
				return SDL_GetTicks() - timePauseStarted;
		}
		return 0;
	}

	void Window::handleBindings()
	{
		for (KeyBinding* kb : bindings)
		{

			if (event.type == SDL_KEYUP && event.key.keysym.sym == kb->getBinding()){
				std::function<void(void)> &fnk = *kb->getFunction();
				fnk();
			}

		}
	}

	void Window::run()
	{
		if(player == nullptr)
		{
			std::cerr << "Error, no player found" << std::endl;
			return;
		}

		setup();

		while (keepRunning)
		{
			if(levelIsFinished())
				keepRunning = loadNextLevel();
			else
				keepRunning = !gameOver();
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
					keepRunning = false;
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_PAUSE)
					timePaused += pause();
				else
					handleEvent(event);

				handleBindings();
			}
			pollNPC();
			moveSprites();
			checkRedraw();
			SDL_Delay(10);
			checkForCollisions();
			deleteOldSprites();
		}
	}

	void Window::setup()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_Surface* surface = IMG_Load("textures/silvia.png");
		SDL_SetWindowIcon(window, surface);
		SDL_FreeSurface(surface);
	}

	void Window::moveSprites()
	{
		for(unsigned short i = 0; i < playerSprites.size(); i++)
			if(playerSprites[i]->isAlive())
				playerSprites[i]->move(window);

		for(unsigned short i = 0; i < npcSprites.size(); i++)
			if(npcSprites[i]->isAlive())
				npcSprites[i]->move(window);
	}
	
	void Window::checkForCollisions()
	{
		if(++loopCounter % 2 == 0)
			return;

		for(unsigned short i = 0; i < playerSprites.size(); i++)
			for(unsigned short n = 0; n < npcSprites.size(); n++)
				if(playerSprites[i]->collision(npcSprites[n], window))
				{
					playerSprites[i]->actOnCollision(npcSprites[n]);
					npcSprites[n]->actOnCollision(playerSprites[i]);
				}
	}

	void Window::deleteOldSprites()
	{
		if(loopCounter % 30 != 0)
			return;

		for (unsigned int i = 0; i < timedTextSprites.size(); i++)
		{
			if (timedTextSprites[i]->isTimeOut())
			{
				delete timedTextSprites[i];
				timedTextSprites.erase(timedTextSprites.begin() + i);
			}
		}


		for (unsigned int i = 0; i < playerSprites.size(); i++)
		{
			if (playerSprites[i]->noLongerInWindow(window) || !playerSprites[i]->isAlive())
			{
				delete playerSprites[i];
				playerSprites.erase(playerSprites.begin() + i);
			}
		}

		for (unsigned int i = 0; i < npcSprites.size(); i++)
		{
			if (npcSprites[i]->noLongerInWindow(window) || !npcSprites[i]->isAlive())
			{
				delete npcSprites[i];
				npcSprites.erase(npcSprites.begin() + i);
			}
		}
	}

	void Window::checkRedraw()
	{
		timeSinceRedraw += SDL_GetTicks() - lastLoopTicks;
		if (1000 / fps < timeSinceRedraw)
		{
			redraw();
			timeSinceRedraw = 0;
		}
		lastLoopTicks = SDL_GetTicks();
	}

	void Window::redraw()
	{
		SDL_RenderClear(renderer);
		background->draw();

		for(unsigned short i = 0; i < playerSprites.size(); i++)
			if(playerSprites[i]->isAlive())
				playerSprites[i]->draw();

		for(unsigned short i = 0; i < npcSprites.size(); i++)
			if(npcSprites[i]->isAlive())
				npcSprites[i]->draw();

		for (Static* sprite : staticSprites)
			sprite->draw();
		for (TimedText* sprite : timedTextSprites)
			sprite->draw();
		SDL_RenderPresent(renderer);
	}

	void Window::handleEvent(const SDL_Event & event)
	{
		for (EventDriven* sprite : eventDrivenSprites)
			sprite->processEvent(event);
	}

	bool Window::levelIsFinished() const
	{
		return npcQueue.empty() && npcSprites.size() == 0;
	}

	bool Window::gameOver() const
	{
		return !player->isAlive();
	}

	SDL_Renderer* Window::getRenderer()const
	{
		return renderer;
	}

	void Window::setFPS(unsigned int fps)
	{
		this->fps = fps;
	}

	int Window::getHeight() const
	{
		int height;
		SDL_GetWindowSize(window, NULL, &height);
		return height;
	}

	int Window::getWidth() const
	{
		int width;
		SDL_GetWindowSize(window, &width, NULL);
		return width;
	}

	void Window::setDefaultFont(std::string fontPath)
	{
		fontManager->setDefaultFont(fontPath);
	}

	std::string Window::getDefaultFont() const
	{
		return fontManager->getDefaultFont();
	}

	void Window::setDefaultFontSize(signed short size)
	{
		fontManager->setDefaultFontSize(size);
	}

	signed short Window::getDefaultFontSize() const
	{
		return fontManager->getDefaultFontSize();
	}

	void Window::setDefaultFontColor(SDL_Color& color)
	{
		fontManager->setDefaultFontColor(color);
	}

	SDL_Color Window::getDefaultFontColor() const
	{
		return fontManager->getDefaultFontColor();
	}
}

