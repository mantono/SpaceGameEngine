#ifndef ENGINE_FONTMANAGER_H_
#define ENGINE_FONTMANAGER_H_

#include <SDL_ttf.h>
#include <string>

namespace engine
{

	class FontManager
	{
	public:
		FontManager();
		virtual ~FontManager();
		void setDefaultFont(std::string);
		std::string getDefaultFont() const;
		void setDefaultFontSize(signed short);
		signed short getDefaultFontSize() const;
		void setDefaultFontColor(SDL_Color&);
		SDL_Color getDefaultFontColor() const;

	private:
		std::string defaultFontPath;
		signed short defaultFontSize;
		SDL_Color defaultFontColor;
	};

}

#endif
