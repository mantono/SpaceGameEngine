#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include "DialogWindow.h"
#include "Sprite.h"
#include "Static.h"
#include "Moveable.h"
#include "EventDriven.h"
#include "FontManager.h"
#include "Player.h"
#include "Text.h"
#include "NPC.h"
#include "Shot.h"
#include "Compare.h"
#include "KeyBinding.h"
#include "TimedText.h"
#include "Level.h"

namespace engine
{

	class Sprite;
	class Window
	{
	public:
		Window(std::string, unsigned int, unsigned int);
		void addPlayer(Player*);
		void addNPC(NPC*);
		void addStatic(Static*);
		void setBackground(Static*);
		void addTimedText(TimedText*);
		void addLevel(Level*);
		void addShot(Shot*);
		int getHeight() const;
		int getWidth() const;
		void run();
		SDL_Renderer* getRenderer()const;
		void setFPS(unsigned int);
		void bindKey(int, std::function<void(void)>);
		void setDefaultFont(std::string);
		std::string getDefaultFont() const;
		void setDefaultFontSize(signed short);
		signed short getDefaultFontSize() const;
		void setDefaultFontColor(SDL_Color&);
		SDL_Color getDefaultFontColor() const;
		~Window();

	private:
		bool keepRunning;
		unsigned short fps;
		unsigned int loopCounter;
		unsigned int timeSinceRedraw;
		unsigned int lastLoopTicks;
		unsigned int windowWidth, windowHeight;
		void setup();
		void addMoveable(Moveable*);
		void addEventDriven(EventDriven*);
		void moveSprites();
		void redraw();
		void checkRedraw();
		void deleteOldSprites();
		void handleEvent(const SDL_Event &);
		void handleBindings();
		void pollNPC();
		void checkForCollisions();
		unsigned int pause();
		void deleteRemainingSprites();
		void deleteRemainingLevels();
		bool levelIsFinished() const;
		bool gameOver() const;
		bool loadNextLevel();
		unsigned int timePaused;

		Player* player;
		Static* background;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;
		FontManager* fontManager;
		Level* currentLevel;
		std::vector<Static*> staticSprites;
		std::vector<Text*> textSprites;
		// std::queue<Moveable*> moveableQueue; //TODO moveables som läggs till ska först läggas till i kön,
		// för att i slutet på run-funktionen läggas i vectorn moveableSprites. Detta för att undvika att vectorn
		// ändras samtidigt som man itererar över den.

		std::vector<Moveable*> npcSprites;
		std::vector<Moveable*> playerSprites;

		std::vector<EventDriven*> eventDrivenSprites;

		std::vector<TimedText*> timedTextSprites;
		std::priority_queue<NPC*, std::vector<NPC*>, Compare> npcQueue;
		std::priority_queue<Level*, std::vector<Level*>, Compare> levels;
		std::vector<KeyBinding*> bindings;
	};
}

#endif


