#pragma once
#include "SDL.h"
#include <string>

namespace Nick
{
	struct RGB
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
	};

	class Texture
	{
	public:
		// Default Constructor
		Texture();
		// Copy Constructor
		Texture(Texture* other);
		// Calls free()
		~Texture();
		// Set texture to image located at path
		bool LoadFromFile(SDL_Renderer* renderer, std::string path, RGB* colorKey = NULL);
		// Delete texture
		void free();
		// Render texture to screen at (x,y)
		void render(SDL_Renderer* renderer, int x, int y, int resizeFactorX, int resizeFactorY, SDL_Rect* clip = NULL);
		// Get image dimensions
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* texture;
		int width;
		int height;
	};
} // namespace
