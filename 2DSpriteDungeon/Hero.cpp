#include "Hero.h"
//complete
using namespace DungeonGame;

void Hero::Initialize(SDL_Renderer* pRenderer, const std::string& moveDown1FilePath, const std::string& moveDown2FilePath,
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
{
	 MoveDownFrame1Texture = LoadTexture(pRenderer, moveDown1FilePath);
	 MoveDownFrame2Texture = LoadTexture(pRenderer, moveDown2FilePath);

	 MoveRightFrame1Texture = LoadTexture(pRenderer, moveRight1FilePath);
	 MoveRightFrame2Texture = LoadTexture(pRenderer, moveRight2FilePath);
	 MoveUpFrame1Texture = LoadTexture(pRenderer, moveUp1FilePath);
	 MoveUpFrame2Texture = LoadTexture(pRenderer, moveUp2FilePath);

	//Item Textures
	//Picking up item
	 PickUp1 = LoadTexture(pRenderer, pickUp1FilePath);
	 PickUp2 = LoadTexture(pRenderer, pickUp2FilePath);
	//UseItem
	 UseItemDown = LoadTexture(pRenderer, useItemDown);
	 UseItemRight = LoadTexture(pRenderer, useItemRight);
	 UseItemUp = LoadTexture(pRenderer, useItemUp);

	//Taking Damage
	//Down
	 HurtDownFrame1 = LoadTexture(pRenderer, hurtDown1FilePath);
	 HurtDownFrame2 = LoadTexture(pRenderer, hurtDown2FilePath);
	//Right
	 HurtRightFrame1 = LoadTexture(pRenderer, hurtRight1FilePath);
	 HurtRightFrame2 = LoadTexture(pRenderer, hurtRight2FilePath);
	// Up
	 HurtUpFrame1 = LoadTexture(pRenderer, hurtUp1FilePath);
	 HurtUpFrame2 = LoadTexture(pRenderer, hurtUp2FilePath);

	//Attacking 
	//Right
	 AttackRightFrame1 = LoadTexture(pRenderer, attackRight1FilePath);
	 AttackRightFrame2 = LoadTexture(pRenderer, attackRight2FilePath);
	 AttackRightFrame3 = LoadTexture(pRenderer, attackRight3FilePath);
	 AttackRightFrame4 = LoadTexture(pRenderer, attackRight4FilePath);
	//Down
	 AttackDownFrame1 = LoadTexture(pRenderer, attackDown1FilePath);
	 AttackDownFrame2 = LoadTexture(pRenderer, attackDown2FilePath);
	 AttackDownFrame3 = LoadTexture(pRenderer, attackDown3FilePath);
	 AttackDownFrame4 = LoadTexture(pRenderer, attackDown4FilePath);
	//Up
	 AttackUpFrame1 = LoadTexture(pRenderer, attackUp1FilePath);
	 AttackUpFrame2 = LoadTexture(pRenderer, attackUp2FilePath);
	 AttackUpFrame3 = LoadTexture(pRenderer, attackUp3FilePath);
	 AttackUpFrame4 = LoadTexture(pRenderer, attackUp4FilePath);
	 MyTexture = MoveDownFrame1Texture;
	 //Animation
	 SecondsAlive = 0.0f;
}
 void Hero::Update(float deltaSeconds, PlayerState& playerState,WorldState& worldState)
{
	 float animationmultiplier = 5.8f;
	 Vector2d direction(0.0f, 0.0f);
	 /*The following allows the player to move in the
	 direction of their choice */
	 bool playerIsAlive = playerState.PlayerHP > 0;
	
	 if (playerIsAlive) //&& playerState.ObtainingItem == false)
	 {
		 if (playerState.WantsToGoUp)
		 {
			 direction.Y = -1.0f;
			
		 }
		 else if (playerState.WantsToGoDown)
		 {
			 direction.Y = 1.0f;

		 }
		 else if (playerState.WantsToGoLeft)
		 {
			 //Mirror the texture? can SDL do that?
			 direction.X = -1.0f;
		 }
		 else if (playerState.WantsToGoRight)
		 {
			 direction.X = 1.0f;
		 }
		 else if (playerState.ObtainingItem)
		 {
			 animationmultiplier = 0.3f;

		 }
		 direction.Normalize();

		 if (direction != Vector2d(0.0f, 0.0f))
		 {
			 playerState.PreviousDirection = direction;
		 }

		 /*if (playerState.WantsToShoot)
		 {
			 Shoot(playerState,playerState.PreviousDirection;
		 }*/

		 Vector2d newPosition = playerState.PlayerPosition;
		 newPosition += direction * 200.0f * deltaSeconds;

		 RoomData roomData = worldState.Rooms[playerState.CurrentRoomIndex];

		 if (roomData.IsWalkableTile(newPosition))
		 {
			 playerState.PlayerPosition = newPosition;
		 }
		 else
		 {
			 //Not sure if roomData is correct here, need to put currRoom or something
			 if (roomData.IsSpaceOutsideMap(newPosition, roomData))
			 {
				 Vector2d desriedRoomPosition = roomData.RoomPosition;
				 int playerPositionType = 0;

				 if (newPosition.X < 0)
				 {
					 desriedRoomPosition.X--;
					 playerPositionType = 1;
				 }
				 else if (newPosition.X >= roomData.TilesPerRow)
				 {
					 desriedRoomPosition.X++;
					 playerPositionType = 2;
				 }
				 else if (newPosition.Y < 0)
				 {
					 desriedRoomPosition.Y--;
					 playerPositionType = 3;
				 }
				 else if (newPosition.Y >= ((int)roomData.Tiles.size() / roomData.TilesPerRow))
				 {
					 desriedRoomPosition.Y++;
					 playerPositionType = 4;
				 }
				 bool foundNewRoom = false;

				 for (unsigned int i = 0; i < worldState.Rooms.size(); ++i)
				 {
					 if (worldState.Rooms[i].RoomPosition == desriedRoomPosition)
					 {
						 playerState.CurrentRoomIndex = i;



						 switch (playerPositionType)
						 {
						 case 1:
							 //og currentposition could be playerState.playerPosition or newPosition
							 playerState.PlayerPosition.X = worldState.Rooms[playerState.CurrentRoomIndex].TilesPerRow - 1;
							 break;
						 case 2:
							 playerState.PlayerPosition.X = 0;
							 break;
						 case 3:
							 playerState.PlayerPosition.Y = (worldState.Rooms[playerState.CurrentRoomIndex].Tiles.size() / worldState.Rooms[playerState.CurrentRoomIndex].TilesPerRow) - 1;
							 break;
						 case 4:
							 playerState.PlayerPosition.Y = 0;
							 break;
						 }

						 foundNewRoom = true;
					 }
				 }
				 if (!foundNewRoom)
				 {
					 printf("I thought the world wasn't flat but it certaintly is out there, you can't go any further.\n");
				 }

			 }
		 }

		 //if player is invincible the duration of invicibility is being
		 //subtracted by time. 
		 if (playerState.InvincibilitySeconds > 0.0f)
		 {
			 playerState.InvincibilitySeconds -= deltaSeconds;
		 }
		 //animation logic
		 //Need to add animation for
		 {
			 SecondsAlive += deltaSeconds;
			 int frame = (int)(SecondsAlive * animationmultiplier) % 2;
			 ///////////////////////////////
			 // all movement animation below. 
			 // hurt animations don't work yet. so for now just 
			 // putting a simple one size fits all link hurt anim
			 //Link moving downwards and downwards hurt animation. 
			 if (frame == 0 && playerState.WantsToGoDown)
			 {
				 MyTexture = MoveDownFrame1Texture;

			 }
			 else if (frame == 1 && playerState.WantsToGoDown)
			 {
				 MyTexture = MoveDownFrame2Texture;
			 }			
			 //Link moving up and getting hurt up
			 if (frame == 0 && playerState.WantsToGoUp)
			 {
				 MyTexture = MoveUpFrame1Texture;

			 }
			 else if (frame == 1 && playerState.WantsToGoUp)
			 {
				 MyTexture = MoveUpFrame2Texture;
			 }
			 //Link going right and getting hurt right
			 if (frame == 0 && playerState.WantsToGoRight)
			 {
				 MyTexture = MoveRightFrame1Texture;

			 }
			 else if (frame == 1 && playerState.WantsToGoRight)
			 {
				 MyTexture = MoveRightFrame2Texture;
			 }
			 //Link moving left and getting hurt right.
			 if (frame == 0 && playerState.WantsToGoLeft)
			 {
				 //theree's an sdl function, will update in a future update. 
				 //need to mirror this somehow
				 MyTexture = MoveRightFrame1Texture;

			 }
			 else if (frame == 1 && playerState.WantsToGoLeft)
			 {
				 //need to mirror this somehow
				 MyTexture = MoveRightFrame2Texture;
			 }

			 if (frame == 0 && playerState.InvincibilitySeconds > 0)
			 {
				 MyTexture = HurtDownFrame2;
			 }
			/* else if (frame == 1 && playerState.InvincibilitySeconds > 0)
			 {
				 MyTexture = HurtDownFrame2;
			 }*/
			 //I want to make it so a person cannot move for about a few seconds
				  //after they obtain an item. but this will be in next patch.
			//REvist
			 if (frame == 0 && playerState.ObtainingItem == true)
			 {
				 //play get item sound.
				 MyTexture = PickUp2;
				 			
			 }
			 else if (frame == 1 && playerState.ObtainingItem == true)
			 {							 
				 //MyTexture = PickUp2;
				 
				 MyTexture = PickUp2;
		
			 }
			 playerState.ObtainingItem = false;
		 }

	 }
	
	 //Need to make this change for the tile, not the player position
	 worldState.CameraPosition = playerState.PlayerPosition;
	//This makes it so, the player position is matching up with the whole sprite. 
	 Position = playerState.PlayerPosition - Vector2d(Size.X * 0.2f, Size.Y * -0.009f);
	 visible = playerIsAlive;
}