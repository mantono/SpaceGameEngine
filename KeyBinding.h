#ifndef KEYBINDING_H
#define KEYBINDING_H
#include "Window.h"
#include <SDL.h>
#include <functional>
namespace engine
{
	class KeyBinding
	{
	friend class Window;

	public:
		typedef void(*fptr)();
		std::function<void(void)>* getFunction();
		int getBinding() const;
		void doFunction();
	private:
		int binding;
		std::function<void(void)> function;
		KeyBinding(int, std::function<void(void)>);
		static KeyBinding* getInstance(int, std::function<void(void)>);
	};




}

#endif
