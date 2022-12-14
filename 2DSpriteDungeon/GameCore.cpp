#include "GameCore.h"
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "HUD.h"
#include "StaticImage.h"
#include "Items.h"
#include "Enemy.h"
#include "Windows.h"

namespace DungeonGame
{
	std::vector<Sprite*> SpriteList;

	RoomData CreateRoom()
	{
		RoomData room = {};
		
		return room;
	}
	bool PlayerState::PlayerHasWon() const
	{
		int numberOfKeys = 0;
		int numberOfSwords = 0;

		for (int i = 0; i < ItemInventory.size(); ++i)
		{
			if (ItemInventory[i] == Item_Key)
			{
				numberOfKeys++;
			}
			else if (ItemInventory[i] == Item_Sword)
			{
				numberOfSwords++;
			}
		}

		return numberOfKeys == 1 && numberOfSwords == 1;
	}
	bool RoomData::IsWalkableTile(const Vector2d inPosition)
	{
		int column = (int)(inPosition.X / TileSizeInPixels.X);
		int row = (int)(inPosition.Y / TileSizeInPixels.Y);

		char currentTile = ' ';
		int index = row * TilesPerRow + column;
		if (index >= 0 && index < (int)Tiles.size())
		{
			 currentTile = Tiles[index];
		}
		
		return currentTile == '.';
	}
	//might need to change currRoom back to roomData. not sure yet
	bool RoomData::IsSpaceOutsideMap(const Vector2d inPosition, const RoomData roomData)
	{

		return inPosition.X < 0 ||
			inPosition.X >= roomData.TilesPerRow ||
			inPosition.Y < 0 ||
			inPosition.Y >= ((int)roomData.Tiles.size() / roomData.TilesPerRow);
	}

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)// , RoomData& roomData)
	{
		playerState.HasFinishedGame = false;
		playerState.PlayerHP = 3;
		playerState.InvincibilitySeconds = 0.0f;
		playerState.PreviousDirection = Vector2d(0.0f, 0.0f);
		playerState.CurrentRoomIndex = 0;
		

		worldState.SecondsSincePlayerDefeat = 0.0f;
		//0 Beginning Room
		{
			RoomData room = CreateRoom();
			room.TilesPerRow = 10;
			//need to change to worldstate.roomposition or something
			room.RoomPosition = { 0,0};
			room.TileSizeInPixels = Vector2d(72.0, 72.0f);

			room.Tiles =
				"##########"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"#........#"
				"##########";

			//Put inventory Items here. 
			//Items
			//item needs to know what room it is in and where in that room is it.
			//the item is being created and it's position is being stored, still not rendering
			worldState.Items.push_back({ true,Item_Sword, Vector2d(1.0f * room.TileSizeInPixels.X, 5.0f * room.TileSizeInPixels.Y) });
			worldState.Items.push_back({ true,Item_Heart, Vector2d(1.0f * room.TileSizeInPixels.X, 6.0f * room.TileSizeInPixels.Y) });
			worldState.Items.push_back({ true,Item_Key, Vector2d(5.0f * room.TileSizeInPixels.X, 20.0f * room.TileSizeInPixels.Y) });
			
			//worldState.Enemies.push_back({ true, false,Vector2d(7.0f * room.TileSizeInPixels.X, 2.0f * room.TileSizeInPixels.Y) });
			worldState.Rooms.push_back(room);
		}
		//1
		//{
		//	RoomData room2 = CreateRoom();
		//	room2.TilesPerRow = 10;
		//	//need to change to worldstate.roomposition or something
		//	room2.RoomPosition = { -1,0 };
		//	room2.TileSizeInPixels = Vector2d(72.0, 72.0f);

		//	room2.Tiles =
		//		".........."
		//		".........."
		//		".........."
		//		".........."
		//		".........."
		//		"##########";

		//	//Put inventory Items here. 
		//	//Items
		//	//item needs to know what room it is in and where in that room is it.
		//	//the item is being created and it's position is being stored, still not rendering
		//	worldState.Items.push_back({ true,Item_Sword, Vector2d(1.0f * room2.TileSizeInPixels.X, 5.0f * room2.TileSizeInPixels.Y) });
		//	worldState.Items.push_back({ true,Item_Heart, Vector2d(1.0f * room2.TileSizeInPixels.X, 6.0f * room2.TileSizeInPixels.Y) });
		//	worldState.Items.push_back({ true,Item_Key, Vector2d(5.0f * room2.TileSizeInPixels.X, 2.0f * room2.TileSizeInPixels.Y) });

		//	worldState.Enemies.push_back({ true, false,Vector2d(7.0f * room2.TileSizeInPixels.X, 2.0f * room2.TileSizeInPixels.Y) });
		//	worldState.Rooms.push_back(room2);
		//}
		
	
		//Filepaths for world
		std::string filePathTopHUD = "Assests/LegendOfZeldaSprites/HUD/TopHUD.bmp";
		std::string filePathPanel = "Assests/LegendOfZeldaSprites/HUD/SideProfile/variant1.bmp";
		std::string filePathGameOver = "Assests/LegendOfZeldaSprites/Link/Death/Bmp/GameOver.bmp";
		std::string filepathVictory = "Assests/LegendOfZeldaSprites/Link/Win/bmp/win.bmp";

		std::string filePathSword = "Assests/LegendOfZeldaSprites/Items/Sword.bmp";
		std::string	filePathHeart = "Assests/LegendOfZeldaSprites/Items/FullHeart.bmp";
		std::string filePathKey = "Assests/LegendOfZeldaSprites/Items/Key.bmp";
		//overworld
		std::string filePathSand =  "Assests/LegendOfZeldaSprites/OverWorld/SpriteSheet/Forest/Tiles/tile009.bmp";
		std::string filePathGround = "Assests/LegendOfZeldaSprites/OverWorld/SpriteSheet/Forest/Tiles/groundtile.bmp";
		std::string filePathWall = "Assests/LegendOfZeldaSprites/OverWorld/SpriteSheet/Forest/Tiles/tile030.bmp";

		

		RoomRenderer* roomRenderer = new RoomRenderer;
		roomRenderer->InitalizeRoomTiles(pRenderer, filePathGround,filePathWall);
		SpriteList.push_back(roomRenderer);

		HUD* topHUD = new HUD;
		topHUD->InitalizeInventorySprites(pRenderer, filePathTopHUD, filePathSword, filePathHeart, 
		filePathKey, filePathPanel, filePathGameOver, filepathVictory);
		//topHUD->Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT * 0.25);
		//topHUD->Position = Vector2d(worldState.CameraPosition.X, worldState.CameraPosition.Y);
		SpriteList.push_back(topHUD);

		//Spawning Items
		RoomData roomData = worldState.Rooms[playerState.CurrentRoomIndex];
		for (unsigned int i = 0; i < worldState.Items.size(); i++)
		{
			std::string itemFilePath = filePathKey;
			//have another line of code for the room position?
			switch (worldState.Items[i].Type)
			{
			case Item_Heart:
				itemFilePath = filePathHeart;
				//need to adjust the texture to proper size
				break;
			case Item_HUD:
				itemFilePath = filePathTopHUD;
				break;
			case Item_Sword:
				itemFilePath = filePathSword;
				break;
			case Item_Key:
				itemFilePath = filePathKey;
				break;
			case Item_Panel:
				itemFilePath = filePathPanel;
				break;

			}
			Items* newItems = new Items;
			newItems->Initialize(pRenderer, itemFilePath);
			newItems->SetItemIndex(i);
			roomData.RoomPosition = { 0,0 };
			newItems->Size = Vector2d(26.0f, 32.0f);
			SpriteList.push_back(newItems);
		}

		//enemy file path
		std::string filepathEnemy = "Assests/LegendOfZeldaSprites/Enemies/GhiniFront.bmp";
		//enemies
		for (unsigned int i = 0; i < worldState.Enemies.size(); i++)
		{
			std::string enemyFilePath = filepathEnemy;
			//have another line of code for the room position?
			
			Enemy* newEnemy = new Enemy;
			newEnemy->Initialize(pRenderer, enemyFilePath);
			newEnemy->SetEnemyIndex(i);
			newEnemy->Size = Vector2d(40.0f, 40.0f);
			SpriteList.push_back(newEnemy);
		}


		//Initial playerState
		playerState.WantsToGoUp = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;
		playerState.CurrentRoomIndex = 0;
		playerState.PlayerPosition = Vector2d(2.0f * roomData.TileSizeInPixels.X, 2.0f * roomData.TileSizeInPixels.Y);
		playerState.ItemInventory.push_back(Item_HUD);
		//playerState.ItemInventory.push_back(Item_Panel);

		//Code below is the initalization of the playable character Link
		//FilePaths for Link
		std::string filePathLinkDown1 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement000.bmp";
		std::string filePathLinkDown2 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement001.bmp";
		std::string filePathLinkRight1 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement002.bmp";
		std::string filePathLinkRight2 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement003.bmp";
		std::string filePathLinkUp1 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement004.bmp";
		std::string filePathLinkUp2 = "Assests/LegendOfZeldaSprites/Link/Movement/Movement005.bmp";
		///SUSSSSS
		std::string filePathLinkPickUp1 = "Assests/LegendOfZeldaSprites/Link/PickUp/PickUp0.bmp";
		std::string filePathLinkPickUp2 = "Assests/LegendOfZeldaSprites/Link/PickUp/PickUp1.bmp";
		//File path for Link Hurt sprites
		std::string filePathLinkHurtDown1 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtDown0.bmp";
		std::string filePathLinkHurtDown2 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtDown1.bmp";
		std::string filePathLinkHurtRight1 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtRight0.bmp";
		std::string filePathLinkHurtRight2 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtRight1.bmp";
		std::string filePathLinkHurtUp1 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtUp0.bmp";
		std::string filePathLinkHurtUp2 = "Assests/LegendOfZeldaSprites/Link/HurtAnimation/HurtUp1.bmp";
		//File path for using item sprites
		std::string filePathLinkUseItemDown = "Assests/LegendOfZeldaSprites/Link/UseItem/UseItemDown.bmp";
		std::string filePathLinkUseItemRight = "Assests/LegendOfZeldaSprites/Link/UseItem/UseItemRight.bmp";
		std::string filePathLinkUseItemUp = "Assests/LegendOfZeldaSprites/Link/UseItem/UseItemUp.bmp";
		//File path for Link's attacks
		std::string filePathLinkAttackDown1 = "Assests/LegendOfZeldaSprites/Link/Attack/Down/SwordDown0.bmp";
		std::string filePathLinkAttackDown2 = "Assests/LegendOfZeldaSprites/Link/Attack/Down/SwordDown1.bmp";
		std::string filePathLinkAttackDown3 = "Assests/LegendOfZeldaSprites/Link/Attack/Down/SwordDown2.bmp";
		std::string filePathLinkAttackDown4 = "Assests/LegendOfZeldaSprites/Link/Attack/Down/SwordDown3.bmp";
			//Right attack
		std::string filePathLinkAttackRight1 = "Assests/LegendOfZeldaSprites/Link/Attack/Right/SwordRight0.bmp";
		std::string filePathLinkAttackRight2 = "Assests/LegendOfZeldaSprites/Link/Attack/Right/SwordRight1.bmp";
		std::string filePathLinkAttackRight3 = "Assests/LegendOfZeldaSprites/Link/Attack/Right/SwordRight2.bmp";
		std::string filePathLinkAttackRight4 = "Assests/LegendOfZeldaSprites/Link/Attack/Right/SwordRight3.bmp";
			//Up attack
		std::string filePathLinkAttackUp1 = "Assests/LegendOfZeldaSprites/Link/Attack/Up/SwordUp0.bmp";
		std::string filePathLinkAttackUp2 = "Assests/LegendOfZeldaSprites/Link/Attack/Up/SwordUp1.bmp";
		std::string filePathLinkAttackUp3 = "Assests/LegendOfZeldaSprites/Link/Attack/Up/SwordUp2.bmp";
		std::string filePathLinkAttackUp4 = "Assests/LegendOfZeldaSprites/Link/Attack/Up/SwordUp3.bmp";


		Hero* newHero = new Hero;
		newHero->Initialize(pRenderer, filePathLinkDown1, filePathLinkDown2, filePathLinkRight1, filePathLinkRight2,
		filePathLinkUp1, filePathLinkUp2, filePathLinkPickUp1, filePathLinkPickUp2,
		filePathLinkHurtDown1, filePathLinkHurtDown2, filePathLinkHurtRight1, filePathLinkHurtRight2,
		filePathLinkHurtUp1, filePathLinkHurtUp2,
		filePathLinkUseItemDown, filePathLinkUseItemRight, filePathLinkUseItemUp,
		filePathLinkAttackDown1, filePathLinkAttackDown2, filePathLinkAttackDown3, filePathLinkAttackDown4,
		filePathLinkAttackRight1, filePathLinkAttackRight2, filePathLinkAttackRight3, filePathLinkAttackRight4,
		filePathLinkAttackUp1, filePathLinkAttackUp2, filePathLinkAttackUp3, filePathLinkAttackUp4);
		newHero->Size = (Vector2d(40.0f,40.0f));
		SpriteList.push_back(newHero);

	/*	HUD* newHUD = new HUD;
		newHUD->InitalizeInventorySprites(pRenderer, filePathTopHUD, filePathSword, filePathHeart, filePathKey);
		SpriteList.push_back(newHUD);*/
	
	}

	void GetInput(PlayerState& playerState,const WorldState& worldState)
	{


		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.HasFinishedGame = true;
			}

			else if (e.type == SDL_KEYDOWN)
			{
				auto KeyCode = e.key.keysym.sym;
				switch (KeyCode)
				{
				case SDLK_ESCAPE:
			
				playerState.HasFinishedGame = true;		
				break;
				//Pausing the game
				case SDLK_SPACE:

					playerState.HasPausedGame = true;
					break;
				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = true;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerState.WantsToGoDown = true;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = true;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto KeyCode = e.key.keysym.sym;
				switch (KeyCode)
				{
				case SDLK_ESCAPE:

					playerState.HasFinishedGame = false;
					break;
				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = false;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerState.WantsToGoDown = false;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = false;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = false;
					break;
				}
			}
		}
	}

	void UpdateGame(float deltaSeconds,PlayerState& playerState,WorldState& worldState, RoomData& roomData)
	{
		RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
		//testX += 20 * deltaSeconds;
		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
			
		}
		if (playerState.PlayerHP <= 0 || playerState.PlayerHasWon())
		{
			worldState.SecondsSincePlayerDefeat += deltaSeconds;

			if (worldState.SecondsSincePlayerDefeat > 2.0f)
			{
				playerState.HasFinishedGame = true;
			}
		}
	}

	void RenderGame(SDL_Renderer* pRenderer,const PlayerState& playerState, const WorldState& worldState)
	{
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Render(pRenderer, playerState,worldState, Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - worldState.CameraPosition);
		}

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)//roomdata used to be here.
	{

		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Cleanup();
			delete SpriteList[i];
		}
		SpriteList.clear();

		Sprite::CleanupTextures();
	}

	//int PositionToIndex(const Position& position, int roomwidth)
	//{
	//	return position.Y * roomwidth + position.X;
	//}




}

