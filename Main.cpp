#pragma once
#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"
#include "InputManager.h"
#include "Texture.h"
#include <string>

#ifndef G_CONST_GLOBAL_VARIABLES
const int SCREEN_WIDTH = 933/2;
const int SCREEN_HEIGHT = 923/2;
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
		Nick::Texture CurrentTexture;
		SDL_Event e;
		
		textureLoaded = CurrentTexture.LoadFromFile(Renderer, "./assets/NickVallejosAlbumCover.png");
		
		if (textureLoaded == false)
		{
			printf("Texture did not load.");
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
			
			if (textureLoaded) 
				CurrentTexture.render(Renderer, 0, 0);

			// Let's Create Viewport 1 and Set Renderer to Viewport1
			// SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2}; // {origin x, origin y, width, height}
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
		Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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