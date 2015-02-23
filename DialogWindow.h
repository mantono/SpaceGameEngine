#ifndef ENGINE_DIALOGWINDOW_H_
#define ENGINE_DIALOGWINDOW_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "../engine/Text.h"
#include "../engine/Window.h"
#include <string>

namespace engine
{

	class DialogWindow
	{
	public:
		DialogWindow(Window*, std::string, int, int, double, int);
		~DialogWindow();
		static DialogWindow* createInstance(Window*);
		SDL_Renderer* getNameRenderer()const;
		void renderText(SDL_Texture*);
		SDL_Texture* createNewTexture();
		
	private:
	
		bool addName;
		void checkName();
		TTF_Font *font;
		SDL_Texture *texture;
		std::string inputText;
		SDL_Color color;
		SDL_Rect area;
		SDL_Rect rect;
		SDL_Window* nameWindow;
		SDL_Renderer* nameRenderer;
		Window* window;
	};

}

#endif
