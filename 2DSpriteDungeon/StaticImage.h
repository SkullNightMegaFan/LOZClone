#pragma once
#include "Sprite.h"
/*
Essentially, this script is used to have a static image
that will stay in the position for the entire game
it is not affected by the camera, thus following the 
player the entire playthrough. in combo with staticImage.cpp
*/
namespace DungeonGame
{
	class StaticImage : public Sprite
	{
	public:

		void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	};
}
