#include "HUD.h"
//complete
using namespace DungeonGame;

void HUD::InitalizeInventorySprites(SDL_Renderer* pRenderer, const std::string& topHUDFilePath, const std::string& swordFilePath, const std::string& heartFilePath, const std::string& keyFilePath, const std::string& panelFilePath,
	const std::string& gameOverFilePath, const std::string& victoryFilePath) 
{	//Items below are for the textures for inventory. 
	//I need key, link's hearts, sword.
	TopHUDTexture = LoadTexture(pRenderer, topHUDFilePath);
	SwordTexture = LoadTexture(pRenderer, swordFilePath);
	HeartTexture = LoadTexture(pRenderer, heartFilePath);
	KeyTexture = LoadTexture(pRenderer, keyFilePath);
	PanelTexture = LoadTexture(pRenderer, panelFilePath);
	GameOverTexture = LoadTexture(pRenderer, gameOverFilePath);
	VictoryTexture = LoadTexture(pRenderer, victoryFilePath);
	
}
void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{

	//Health Display heart shows up
	for (unsigned int i = 0; i < playerState.PlayerHP; ++i)
	{
		MyTexture = HeartTexture;
		//general hud
		if (MyTexture != nullptr)
		{

			SDL_Rect destRect = {
				 WINDOW_WIDTH * .75f + 48.0f * i,
				 100.0f,
				30.0f,
				30.0f, };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

	}

	//Inventory
	for (unsigned int i = 0; i < playerState.ItemInventory.size(); ++i)
	{
		int HUDActive = 0;
		ItemType currItem = playerState.ItemInventory[i];
		switch (currItem)
		{
		case Item_HUD:
			MyTexture = nullptr;
			HUDActive++;

			break;
		case Item_Sword:
			MyTexture = SwordTexture;
			break;
		case Item_Heart:
			MyTexture = nullptr;// HeartTexture;
			break;
		case Item_Key:
			MyTexture = KeyTexture;
			break;
		case Item_Panel:
			MyTexture = PanelTexture;
			break;
		default:
			MyTexture = nullptr;
			break;

		}	
		//general hud
	

		if (MyTexture != nullptr)
		{
		

			/////////////////////////
			SDL_Rect destRect = {
				 (int)(16.0f + 48.0f * i),
				 (int)16.0f,
				(int)Size.X,
				(int)Size.Y, };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

		if (playerState.PlayerHP <= 0)
		{
			SDL_Rect destRect = {
				0,
				0,
				WINDOW_WIDTH,
				WINDOW_HEIGHT };
			SDL_RenderCopy(pRenderer, GameOverTexture, nullptr, &destRect);
		}
		if (playerState.PlayerHasWon())
		{
			SDL_Rect destRect = {
				0,
				0,
				WINDOW_WIDTH,
				WINDOW_HEIGHT };
			SDL_RenderCopy(pRenderer, VictoryTexture, nullptr, &destRect);
		}
		if (HUDActive == 1)
		{
			SDL_Rect destRect = {
				0,
				0,
				WINDOW_WIDTH,
				0 };
			SDL_RenderCopy(pRenderer, TopHUDTexture, nullptr, &destRect);
		}
		
	}
	

	
}