#pragma once
#include "Texture.h"
#include "SDL.h"

namespace Nick
{
	class Animation
	{
	public:
		Animation();
		Animation(Texture* texture, int spriteWidth, int spriteHeight);
		~Animation();
		SDL_Rect* GetFrame(int index);
		void Update(float deltaTime, SDL_Renderer* renderer, int posX, int posY, int resizeX, int resizeY);
	private:
		int totalFrames;
		int currentFrame;
		float frameDuration;
		float accumulator;
	private:
		Texture* spriteSheet;
		SDL_Rect* frames;
	};
} // namespace
