#pragma once
#include "Vector2.hpp"

namespace Nick
{
	class InputManager
	{
	public:
		bool JumpButton, JumpButtonDown, JumpButtonUp;
		bool PauseButton;
		Nick::Vector2<float>* DirectionalInput;
	public:
		InputManager();
		~InputManager();
	private:
		void StoreKeyboardInput();
	public:
		void Update();
	};
}