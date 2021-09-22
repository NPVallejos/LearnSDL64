#pragma once

namespace Nick
{
	class Timer
	{
	public:
		void Tick();
		inline float GetDeltaTime() { return deltaTime;  }
		inline static Timer* GetInstance()
		{
			return s_instance = (s_instance != nullptr) ? s_instance : new Timer();
		}
		~Timer();
	private:
		Timer();
		static Timer* s_instance;
		float deltaTime;
		float lastTime;
	};
} // namespace