#pragma once
#include "Sprite.h"
//completely done
namespace DungeonGame
{
	class Hero : public Sprite
	{
		
	public:
		//This is going to be super long. I need to initalize every single possible sprite for Link
		void Initialize(SDL_Renderer* pRenderer, const std::string& moveDown1FilePath, const std::string& moveDown2FilePath,
			const std::string& moveRight1FilePath, const std::string& moveRight2FilePath, const std::string& moveUp1FilePath,
			//I plan to mirror the right facing sprites for the left facing Link
			const std::string& moveUp2FilePath, //Above are all the movements. next is pick up sprites
			const std::string& pickUp1FilePath, const std::string& pickUp2FilePath, //next up is damage taking
			const std::string& hurtDown1FilePath, const std::string& hurtDown2FilePath,
			const std::string& hurtRight1FilePath, const std::string& hurtRight2FilePath,
			const std::string& hurtUp1FilePath, const std::string& hurtUp2FilePath,//next up is use item!
			const std::string& useItemDown, const std::string& useItemRight, const std::string& useItemUp, //need to mirror for right
			//and finally attacking
			//down
			const std::string& attackDown1FilePath, const std::string& attackDown2FilePath, const std::string& attackDown3FilePath, const std::string& attackDown4FilePath,
			//right, need to mirror. 
			const std::string& attackRight1FilePath, const std::string& attackRight2FilePath, const std::string& attackRight3FilePath, const std::string& attackRight4FilePath,
			const std::string& attackUp1FilePath, const std::string& attackUp2FilePath, const std::string& attackUp3FilePath, const std::string& attackUp4FilePath)
			;
		virtual void Update(float deltaSeconds,PlayerState& playerState,WorldState& worldState);

	private:
		/*Projectile for link. It should only be a projectile when Link has full health. */
	//	void Shoot(PlayerState& playerState, const Vector2d& direction);
		//Movement Texture
		SDL_Texture* MoveDownFrame1Texture;
		SDL_Texture* MoveDownFrame2Texture;
		SDL_Texture* MoveRightFrame1Texture;
		SDL_Texture* MoveRightFrame2Texture;
		SDL_Texture* MoveUpFrame1Texture;
		SDL_Texture* MoveUpFrame2Texture;

		//Item Textures
		//Picking up item
		SDL_Texture* PickUp1;
		SDL_Texture* PickUp2;
		//UseItem
		SDL_Texture* UseItemDown;
		SDL_Texture* UseItemRight;
		SDL_Texture* UseItemUp;

		//Taking Damage
		//Down
		SDL_Texture* HurtDownFrame1;
		SDL_Texture* HurtDownFrame2;
		//Right
		SDL_Texture* HurtRightFrame1;
		SDL_Texture* HurtRightFrame2;
		// Up
		SDL_Texture* HurtUpFrame1;
		SDL_Texture* HurtUpFrame2;

		//Attacking 
		//Right
		SDL_Texture* AttackRightFrame1;
		SDL_Texture* AttackRightFrame2;
		SDL_Texture* AttackRightFrame3;
		SDL_Texture* AttackRightFrame4;
		//Down
		SDL_Texture* AttackDownFrame1;
		SDL_Texture* AttackDownFrame2;
		SDL_Texture* AttackDownFrame3;
		SDL_Texture* AttackDownFrame4;
		//Up
		SDL_Texture* AttackUpFrame1;
		SDL_Texture* AttackUpFrame2;
		SDL_Texture* AttackUpFrame3;
		SDL_Texture* AttackUpFrame4;

		float SecondsAlive;

	};
}
