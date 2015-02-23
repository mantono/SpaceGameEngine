#ifndef ENGINE_EVENTDRIVEN_H_
#define ENGINE_EVENTDRIVEN_H_

#include <SDL.h>

namespace engine
{
	class EventDriven
	{
	public:
		virtual void processEvent(const SDL_Event &) = 0;
		virtual ~EventDriven();
	};

}

#endif
