#include "StaticImage.h"

using namespace DungeonGame;
//completely finished

void StaticImage::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	if (MyTexture != nullptr)
				{
		SDL_Rect destRect = { (int)Position.X ,(int)Position.Y , (int)Size.X, (int)Size.Y };
		SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
	
	}

}