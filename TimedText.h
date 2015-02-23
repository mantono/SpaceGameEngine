#ifndef TIMEDTEXT_H_
#define TIMEDTEXT_H_
#include "Text.h"

namespace engine
{
	class TimedText: public Text
	{

	public:
		static TimedText* createInstance(Window*, std::string, int, int, double);		
		bool isTimeOut();
		~TimedText();
	protected:
		TimedText(Window*, std::string, int, int, double);

	private:
		unsigned int startTime;
		unsigned int endTime;
		TTF_Font *font;
		std::string text;
		std::string fontPath;
		SDL_Color color;
		SDL_Texture *fontTexture;
		signed short fontSize;
	};
}
#endif
