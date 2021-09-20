#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"
#include <string>

#ifndef G_CONST_GLOBAL_VARIABLES
const int SCREEN_WIDTH = 320*2;
const int SCREEN_HEIGHT = 180*2;
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
void RenderSomeRectangles(SDL_Rect* Viewport);
#endif

#ifndef G_INPUT_ENUMERATORS
/* TODO: Create enums for multiple inputs (i.e. Jump => {Keycode, JoystickButton} = {SDLK_SPACEBAR, JOYSTICK_BUTTON_A} */
#endif

template <class T>
class Vector2
{
public:
	T x;
	T y;
public:
	Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}
	void Clear()
	{
		this->x = 0;
		this->y = 0;
	}
};

class InputManager
{
public:
	bool JumpButton, JumpButtonDown, JumpButtonUp;
	bool PauseButton;
	Vector2<float>* DirectionalInput;
public:
	InputManager()
	{
		JumpButton = JumpButtonDown = JumpButtonUp = false;
		DirectionalInput = new Vector2<float>(0, 0);
	}
	~InputManager()
	{
		delete DirectionalInput;
	}
private:
	void StoreKeyboardInput()
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
public:
	void Update()
	{
		// Clear select input from previous frame
		DirectionalInput->Clear();
		JumpButtonDown = JumpButtonUp = false;

		// Handle Storing Keyboard Input
		StoreKeyboardInput();
	}
};

int main(int argc, char* argv[])
{
	if (Initialize())
	{
		InputManager input;
		SDL_Event e;
		CurrentTexture = LoadTexture("./assets/NickVallejosAlbumCover.png");
		bool quit = false;


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
				
			// Let's Create Viewport 1 and Set Renderer to Viewport1
			SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2}; // {origin x, origin y, width, height}
			SDL_RenderSetViewport(Renderer, &topLeftViewport);
			RenderSomeRectangles(&topLeftViewport);

			// Viewport 2 - let's render an image
			SDL_Rect topRightViewport = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_RenderSetViewport(Renderer, &topRightViewport);
			SDL_RenderCopy(Renderer, CurrentTexture, NULL, NULL);

			// Viewport 3 - Let's render rectangles over our image
			SDL_Rect bottomViewport = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
			SDL_RenderSetViewport(Renderer, &bottomViewport);
			SDL_RenderCopy(Renderer, CurrentTexture, NULL, NULL);
			RenderSomeRectangles(&bottomViewport);

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

void RenderSomeRectangles(SDL_Rect* Viewport)
{
	// Lets render a red fill rectangle
	SDL_Rect fillRect = { Viewport->w / 4, Viewport->h / 4, Viewport->w / 2, Viewport->h / 2 }; // { x-coordinate, y-coordinate, width, height };
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF); // (r, g, b, a) - it's set to red with full opacity
	SDL_RenderFillRect(Renderer, &fillRect);

	// Lets render a green outline of a rectangle now
	SDL_Rect outlineRect = { Viewport->w / 6, Viewport->h / 6, Viewport->w * 2 / 3, Viewport->h * 2 / 3 };
	SDL_SetRenderDrawColor(Renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(Renderer, &outlineRect);

	// Lets draw a blue line
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(Renderer, 0, Viewport->h / 2, Viewport->w, Viewport->h / 2);

	// Lets draw a yellow dotted line
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < Viewport->h; i += 2)
	{
		SDL_RenderDrawPoint(Renderer, Viewport->w / 2, i);
	}
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