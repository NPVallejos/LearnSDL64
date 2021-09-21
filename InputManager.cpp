#include "InputManager.h"
#include "SDL.h"

namespace Nick
{
	InputManager::InputManager()
	{
		JumpButton = JumpButtonDown = JumpButtonUp = false;
		DirectionalInput = new Nick::Vector2<float>(0, 0);
	}

	InputManager::~InputManager()
	{
		delete DirectionalInput;
	}

	void InputManager::StoreKeyboardInput()
	{
		// Handle Keyboard Input
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			if (JumpButton == false)
			{
				JumpButtonDown = true;
				JumpButton = true;
			}
		}
		else if (JumpButton == true)
		{
			JumpButton = false;
			JumpButtonUp = true;
		}
		if (currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			PauseButton = true;
		}
		else if (PauseButton = true)
		{
			PauseButton = false;
		}
		if (currentKeyStates[SDL_SCANCODE_A])
		{
			DirectionalInput->x = -1;
		}
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			DirectionalInput->x = 1;
		}
		if (currentKeyStates[SDL_SCANCODE_W])
		{
			DirectionalInput->y = 1;
		}
		if (currentKeyStates[SDL_SCANCODE_S])
		{
			DirectionalInput->y = -1;
		}
	}

	void InputManager::Update()
	{
		// Clear select input from previous frame
		DirectionalInput->Clear();
		JumpButtonDown = JumpButtonUp = false;

		// Handle Storing Keyboard Input
		StoreKeyboardInput();
	}
} // namespace 