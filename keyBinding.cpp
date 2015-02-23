#include "Window.h"
#include "KeyBinding.h"

namespace engine
{
	KeyBinding::KeyBinding(int i, std::function<void(void)> func) :binding(i), function(func)
	{
		
	}

	KeyBinding* KeyBinding::getInstance(int i , std::function<void(void)> func)
	{
		KeyBinding *b = new KeyBinding(i, func);
		return b;
	}

	std::function<void(void)>* KeyBinding::getFunction()
	{
		return &function;
	}

	

	int KeyBinding::getBinding() const
	{
		return binding;
	}



}
