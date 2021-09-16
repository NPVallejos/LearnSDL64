#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"
#include <string>

#ifndef G_CONST_GLOBAL_VARIABLES
const int SCREEN_WIDTH = 245;
const int SCREEN_HEIGHT = 189;
const int KEY_PRESS_SURFACE_TOTAL = 4;
#endif G_CONST_GLOBAL_VARIABLES

// Step 0. Declare our SDL Window and SDL Surfaces
#ifndef G_SDL_VARIABLES
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Texture* CurrentTexture = NULL;
#endif

#ifndef G_FUNCTION_SIGNATURES
bool Initialize();
void Close();
SDL_Texture* LoadTexture(std::string path);
#endif

#ifndef G_INPUT_ENUMERATORS
/* TODO: Create enums for multiple inputs (i.e. Jump => {Keycode, JoystickButton} = {SDLK_SPACEBAR, JOYSTICK_BUTTON_A} */
#endif

int main(int argc, char* argv[])
{
	if (Initialize())
	{
		CurrentTexture = LoadTexture("./assets/focusing.gif");

		if (CurrentTexture != NULL)
		{
			bool quit = false;

			SDL_Event e;

			// Main Game Loop
			while (quit == false)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
						case SDL_QUIT:
						{
							quit = true;
							break;
						}
						case SDL_KEYDOWN:
						{
							SDL_Keycode keycode = e.key.keysym.sym;
							printf("Pressed key %s\n", SDL_GetKeyName(keycode));
							switch (keycode)
							{
								case SDLK_DOWN:
									break;
								case SDLK_UP:
									break;
								case SDLK_LEFT:
									break;
								case SDLK_RIGHT:
									break;
								case SDLK_ESCAPE:
									quit = true;
									break;
								default:
									break;
							}
							break;
						}
						case SDL_JOYBUTTONDOWN:
						{
							printf("Pressed a button");
							break;
						}
						default:
						{
							break;
						}
					}
				}
				// Clear screeb
				SDL_RenderClear(Renderer);

				// Render Texture to screen
				SDL_RenderCopy(Renderer, CurrentTexture, NULL, NULL);

				// Updates our screen
				SDL_RenderPresent(Renderer);
			}
		}
		else
		{
			printf("Failed to load texture!\n");
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

SDL_Texture* LoadTexture(std::string path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	
	if (loadedSurface != NULL) 
	{
		texture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);

		if (texture != NULL)
		{
			SDL_FreeSurface(loadedSurface);
			loadedSurface = NULL;
		}
		else
		{
			printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
		}
	}
	else
	{
		printf("Unable to load %s! IMG_Error: %s\n", path.c_str(), IMG_GetError());
	}

	return texture;
}

void Close()
{
	// Step 6. Clean up, clean up, everybody clean up
	SDL_DestroyTexture(CurrentTexture);
	CurrentTexture = NULL;

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;

	// Step 7. Quit life
	IMG_Quit();
	SDL_Quit();
}