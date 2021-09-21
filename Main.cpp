#pragma once
#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"
#include "InputManager.h"
#include "Texture.h"
#include <string>

#ifndef G_CONST_GLOBAL_VARIABLES
const int TARGET_RESOLUTION_X = 320;
const int TARGET_RESOLUTION_Y = 180;
const int CURRENT_RESOLUTION_X = 1600;
const int CURRENT_RESOLUTION_Y = 900;
const int MAX_RESIZE_MULTIPLIER_X = 6;
const int MAX_RESIZE_MULTIPLIER_Y = 6;
const int RESOLUTION_RATIO_X = CURRENT_RESOLUTION_X / TARGET_RESOLUTION_X;
const int RESOLUTION_RATIO_Y = CURRENT_RESOLUTION_Y / TARGET_RESOLUTION_Y;
const std::string WINDOW_TITLE = "LearnSDL64";
#endif G_CONST_GLOBAL_VARIABLES

// Step 0. Declare our SDL Window and SDL Surfaces
#ifndef G_SDL_VARIABLES
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
#endif

#ifndef G_FUNCTION_SIGNATURES
bool Initialize();
void Close();
#endif

#ifndef G_INPUT_ENUMERATORS
/* TODO: Create enums for multiple inputs (i.e. Jump => {Keycode, JoystickButton} = {SDLK_SPACEBAR, JOYSTICK_BUTTON_A} */
#endif

int main(int argc, char* argv[])
{
	if (Initialize())
	{
		bool quit = false;
		bool textureLoaded = false;

		Nick::InputManager input;
		Nick::Texture LevelTexture;
		Nick::Texture PlayerTexture;
		SDL_Event e;
		
		if (LevelTexture.LoadFromFile(Renderer, "./assets/320x180.png") == false 
			|| PlayerTexture.LoadFromFile(Renderer, "./assets/player_16x16.png") == false)
		{
			quit = true;
		}

		// Main Game Loop
		while (quit == false)
		{
			// Poll Event
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
					case SDL_QUIT:
					{
						quit = true;
						break;
					}
					default:
					{
						break;
					}
				}
			}

			// Update Input
			input.Update();
			
			if (input.PauseButton)
			{
				quit = true;
			}
			if (input.JumpButtonDown)
			{
				printf("JumpButtonDown\n");
			}
			if (input.JumpButtonUp) {
				printf("JumpButtonUp\n");
			}

			// Clear screen
			SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(Renderer);
			
			LevelTexture.render(Renderer, 0, 0, RESOLUTION_RATIO_X, RESOLUTION_RATIO_Y);
			PlayerTexture.render(Renderer, 0, 0, RESOLUTION_RATIO_X, RESOLUTION_RATIO_Y);
			PlayerTexture.render(Renderer, 16, 0, RESOLUTION_RATIO_X, RESOLUTION_RATIO_Y);
			

			// Let's Create Viewport 1 and Set Renderer to Viewport1
			// SDL_Rect topLeftViewport = {0, 0, TARGET_RESOLUTION_X/2, TARGET_RESOLUTION_Y/2}; // {origin x, origin y, width, height}
			// SDL_RenderSetViewport(Renderer, &topLeftViewport);

			// Updates our screen
			SDL_RenderPresent(Renderer);
		}
	}
	else
	{
		printf("Failed to initalize!\n");
	}

	Close();

	return 0;
}

bool Initialize()
{
	bool success = true;

	// Step 1. Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Step 2. Initialize our SDL window
		Window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CURRENT_RESOLUTION_X, CURRENT_RESOLUTION_Y, SDL_WINDOW_SHOWN);

		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Step 3. Initialize our renderer
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				// Set screen color to white
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Optionally, initialize SDL_image here
			}
		}
	}

	return success;
}

void Close()
{
	// Step 6. Clean up, clean up, everybody clean up
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;

	// Step 7. Quit life
	IMG_Quit();
	SDL_Quit();
}