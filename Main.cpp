#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"
#include <string>

#ifndef G_CONST_GLOBAL_VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int KEY_PRESS_SURFACE_TOTAL = 4;
#endif G_CONST_GLOBAL_VARIABLES

// Step 0. Declare our SDL Window and SDL Surfaces
#ifndef G_SDL_VARIABLES
SDL_Window* Window = NULL;
SDL_Surface* ScreenSurface = NULL;
SDL_Surface* CurrentImageSurface = NULL;
SDL_Surface* KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
#endif

#ifndef G_FUNCTION_SIGNATURES
bool Initialize();
bool LoadMedia(std::string filename);
void Close();
SDL_Surface* LoadSurface(std::string path);
#endif

#ifndef G_INPUT_ENUMERATORS
/* TODO: Create enums for multiple inputs (i.e. Jump => {Keycode, JoystickButton} = {SDLK_SPACEBAR, JOYSTICK_BUTTON_A} */
#endif

int main(int argc, char* argv[])
{
	if (Initialize())
	{
		if (LoadMedia("./assets/HelloWorld.bmp"))
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

				SDL_BlitSurface(CurrentImageSurface, NULL, ScreenSurface, NULL);

				SDL_UpdateWindowSurface(Window);
			}
		}
		else
		{
			printf("Failed to load media!\n");
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
			// Step 3. Initialize our SDL surface
			ScreenSurface = SDL_GetWindowSurface(Window);
		}
	}

	return success;
}

bool LoadMedia(std::string filename)
{
	bool success = true;

	CurrentImageSurface = IMG_Load(filename.c_str());

	if (CurrentImageSurface == NULL)
	{
		printf("Unable to load image %s, SDL_Error: %s\n", filename, IMG_GetError());
		success = false;
	}

	return success;
}

void Close()
{
	// Step 6. Clean up, clean up, everybody clean up
	SDL_FreeSurface(CurrentImageSurface);
	CurrentImageSurface = NULL;

	SDL_DestroyWindow(Window);
	Window = NULL;

	// Step 7. Quit life
	SDL_Quit();
}