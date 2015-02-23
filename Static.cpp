#include "Static.h"
#include "Window.h"

namespace engine
{
	Static::Static(Window* window, std::string imagePath, signed int x, signed int y, int width, int height)
	:Sprite(window, imagePath, x, y, width, height)
	{}

	Static::Static(Window* window, signed int x, signed int y, int width, int height)
	:Sprite(window, x, y, width, height)
	{}

	Static* Static::createInstance(Window* window, std::string imagePath, signed int x, signed int y, int width, int height)
	{
		Static* sprite = new Static(window, imagePath, x, y, width, height);
		window->addStatic(sprite);
		return sprite;
	}
.
	void Static::setBackground(Window* window, std::string imagePath, int width, int height)
	{
		window->setBackground(new Static(window, imagePath, 0, 0, width, height));
	}


	Static::~Static()
	{}

}
