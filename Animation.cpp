#include "Animation.h"

namespace Nick
{
	Animation::Animation()
	{
		totalFrames = 0;
		currentFrame = 0;
		frameDuration = 100.0f / 1000.0f;
		accumulator = 0.0f;
		spriteSheet = NULL;
		frames = NULL;
	}

	Animation::Animation(Texture* texture, int spriteWidth, int spriteHeight)
	{
		totalFrames = 0;
		currentFrame = 0;
		frameDuration = 100.0f / 1000.0f;
		accumulator = 0.0f;

		// Warning: Assumes that sprites are tightly packed in the sprite sheet!
		spriteSheet = texture;
		if (spriteSheet != NULL)
		{
			totalFrames = (spriteSheet->getWidth() * spriteSheet->getHeight()) / (spriteWidth * spriteHeight);
			frames = new SDL_Rect[totalFrames];
			
			int rows = spriteSheet->getHeight() / spriteHeight;
			int columns = spriteSheet->getWidth() / spriteWidth;

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					frames[c].x = c * spriteWidth;
					frames[c].y = r * spriteHeight;
					frames[c].w = 16;
					frames[c].h = 16;
				}
			}
		}
	}

	Animation::~Animation()
	{
		delete[] frames;
	}

	SDL_Rect* Animation::GetFrame(int index)
	{
		return &frames[index];
	}

	void Animation::Update(float deltaTime, SDL_Renderer* renderer, int posX, int posY, int resizeX, int resizeY)
	{
		accumulator += deltaTime;
		if (accumulator > frameDuration)
		{
			accumulator = 0;
			currentFrame = (currentFrame + 1) % totalFrames;
		}
		spriteSheet->render(renderer, posX, posY, resizeX, resizeY, &frames[currentFrame]);
	}
}