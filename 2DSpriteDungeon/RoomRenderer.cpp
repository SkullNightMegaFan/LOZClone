#include "RoomRenderer.h"
//complete
using namespace DungeonGame;

void RoomRenderer::InitalizeRoomTiles(SDL_Renderer* pRenderer, const std::string& floorFilePath, const std:: string& wallFilePath)
{
	FloorTexture = LoadTexture(pRenderer, floorFilePath);
	WallTexture = LoadTexture(pRenderer, wallFilePath);
}

void RoomRenderer::Render(SDL_Renderer* pRenderer, const PlayerState& playerState,const WorldState& worldState,const Vector2d& baseTranslation)
{
	int columnsRendered = 0;
	int rowsRendered = 0;

	RoomData roomData = worldState.Rooms[playerState.CurrentRoomIndex];

	for (unsigned int i = 0; i < roomData.Tiles.size(); ++i)
	{
		char currentTile = roomData.Tiles[i];
		switch (currentTile)
		{
		case '#' :
			MyTexture = WallTexture;
			break;
		case '.':
			MyTexture = FloorTexture;
			break;
		default:
			MyTexture = nullptr;
			break;

		}
		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = { 
				columnsRendered * (int)roomData.TileSizeInPixels.X + (int)baseTranslation.X,
				rowsRendered * (int)roomData.TileSizeInPixels.Y + (int)baseTranslation.Y,
				(int)roomData.TileSizeInPixels.X,
				(int)roomData.TileSizeInPixels.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
		columnsRendered++;
		if (columnsRendered % roomData.TilesPerRow == 0)
		{
			rowsRendered++;
			columnsRendered = 0;
		}
	}
}