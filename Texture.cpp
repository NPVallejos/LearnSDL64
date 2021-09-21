#include "Texture.h"
#include "SDL.h"
#include "stdio.h"
#include "SDL_image.h"

namespace Nick
{
	Texture::Texture()
	{
		texture = NULL;
		width = 0;
		height = 0;
	}

	Texture::~Texture()
	{
		free();
	}
	
	bool Texture::LoadFromFile(SDL_Renderer* renderer, std::string path, RGB* colorKey)
	{
		bool successfullyCreatedTexture = false;

		// Clear previously loaded texure if any exists
		free();

		// Load our image into an SDL surface
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface != NULL)
		{
			if (colorKey != NULL)
			{
				// Color key image
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));
			}
			
			// Create and set texture
			texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

			if (texture != NULL)
			{
				successfullyCreatedTexture = true;
				
				// Set width and height to image dimensions
				width = loadedSurface->w;
				height = loadedSurface->h;

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

		return successfullyCreatedTexture;
	}
	
	void Texture::free()
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}
	// TODO: Load in a texture of size 400x400
	// Create a window of size 200x200
	// Render the texture at (0,0) by calling render(Renderer, 0, 0)
	// Check if the texture fits the screen
	// If not, then this function needs to be passed in a SDL_Rect Viewport
	void Texture::render(SDL_Renderer* renderer, int x, int y, int resizeFactorX, int resizeFactorY)
	{
		SDL_Rect renderQuad = { x * resizeFactorX, y * resizeFactorY, width * resizeFactorX, height * resizeFactorY };
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	}
	
	int Texture::getWidth()
	{
		return width;
	}

	int Texture::getHeight()
	{
		return height;
	}
} // namespace