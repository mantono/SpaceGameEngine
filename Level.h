#ifndef ENGINE_LEVEL_H_
#define ENGINE_LEVEL_H_

namespace engine
{
	class Window;
	class Level
	{
	public:
		Level(Window*, unsigned int);
		virtual void load() = 0;
		virtual void after() = 0;
		unsigned int getLevel();
		virtual ~Level();
	protected:
		Window* window;
		const unsigned int level;
	};

	}

#endif
