#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class RoomRenderer : public Sprite
	{
	public:

		//Need to add more tiles.
		void InitalizeRoomTiles(SDL_Renderer* pRenderer, const std::string& floorFilepath, const std::string& wallFilepath);

		//void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const RoomData roomData, const Vector2d& baseTranslation);

		virtual void  Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);
		

	private:
		//Textures that are loaded for the room tiles.
		SDL_Texture* FloorTexture;
		SDL_Texture* WallTexture;

	};
}
