#include "Timer.h"
#include "SDL.h"

namespace Nick
{
	Timer* Timer::s_instance = nullptr;

	Timer::Timer()
	{
		deltaTime = 0.0f; 
		lastTime = 0.0f;
	}

	Timer::~Timer()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
		}
	}

	void Timer::Tick()
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000;
		lastTime = SDL_GetTicks();
	}

}