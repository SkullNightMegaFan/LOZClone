#pragma once
#include "Sprite.h"
//completely finished.
namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:

		void InitalizeInventorySprites(SDL_Renderer* pRenderer, const std::string& topHUDFilePath,  const std::string& swordFilePath,const std::string& heartFilePath, const std::string& keyFilePath, const std::string& panelFilePath, 
			const std::string& gameOverFilePath, const std::string& victoryFilePath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);


	private:
		SDL_Texture* TopHUDTexture;
		SDL_Texture* HeartTexture;
		SDL_Texture* KeyTexture;
		SDL_Texture* MapTexture;
		SDL_Texture* SwordTexture;
		SDL_Texture* PanelTexture;
		SDL_Texture* GameOverTexture;
		SDL_Texture* VictoryTexture;
		//Aw yeah, we're making a zelda clone.
		//Get excited.
		
	};
}

