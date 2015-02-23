#ifndef TEXT_H_
#define TEXT_H_
#include "SDL_ttf.h"
#include "Static.h"
#include <string>

namespace engine
{
	class Text: public Static
	{

	public:
		static Text* createInstance(Window*, std::string, int, int);
		void createNewTexture();
		void setFont(std::string);
		void setFontSize(signed short);
		void setText(std::string);
		void setText(int);
		void setText(float);
		void setText(double);
		std::string getText() const;
		void setColor(SDL_Color&);
		Text(Window*, std::string, int, int);
		~Text();
	protected:
		

	private:
		
		std::string text;
		std::string fontPath;
		SDL_Color color;
		TTF_Font *font;
		SDL_Texture *fontTexture;
		signed short fontSize;
	};
}
#endif
