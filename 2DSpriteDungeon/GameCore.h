#pragma once
#include "SDL.h"
#include <string>
#include <vector>


namespace DungeonGame
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			 X(0.0f),
			 Y(0.0f)
		{

		}
		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{

		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;

		}
		bool operator!=(const Vector2d& otherPosition) const
		{
			return!(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d& rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}
		const Vector2d operator+(const Vector2d& rhs) const
		{
			return (Vector2d(*this) += rhs);
		}

		Vector2d& operator-=(const Vector2d& rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}
		const Vector2d operator-(const Vector2d& rhs) const
		{
			return (Vector2d(*this) -= rhs);
		}
		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return (Vector2d(*this) *= scalar);
		}
		//Essentially finding the hypothenuse by using the X and Y values as the adjacent and opposite
		float GetLength()
		{
			return sqrt(X * X + Y * Y);
		}
		//essentially rounds the length to be a singular number.
		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}
	};

			
	enum ItemType
	{
		Item_Key,
		Item_Heart,
		Item_Sword,
		Item_HUD,
		Item_Panel
	};
	/*enum EnemyType
	{
		Enemy_OctoRock,
		Enemy_Moblin,
	Enemy_Lynl,
	Enemy_Moblin,
	Enemy_Ghini,
	Enemy_Zora
	};*/
	struct PlayerState
	{
		//UI type stuff
		bool HasFinishedGame;
		bool HasPausedGame;

		//Movement
		bool WantsToGoUp;
		bool WantsToGoDown;
		bool WantsToGoLeft;
		bool WantsToGoRight;

		bool ObtainingItem;
		std::vector<ItemType> ItemInventory;
		//movement between room and within rooms. 
		int CurrentRoomIndex;
		Vector2d PlayerPosition;
		Vector2d PreviousDirection;

		int PlayerHP;
		float InvincibilitySeconds;

		//float SwordCoolDownSeconds

		bool PlayerHasWon() const;
	};
	struct ItemData
	{
		bool Alive;
		ItemType Type;
		Vector2d Position;
		

	};
	struct EnemyData
	{
		bool Alive;
		bool Hurt;
		//Will add enemy type in a future version.
		//EnemyType Type;
		Vector2d Position;
	};

	struct RoomData
	{
		int TilesPerRow;

		//Position RoomPosition;
		std::string Tiles;
		Vector2d TileSizeInPixels;

		Vector2d RoomPosition;
		
		/*
		Add this stuff later
		*/
	//	vector<InventoryItem> Inventory;
		//std::vector<LockedDoorData> LockedDoors;

		bool IsWalkableTile(const Vector2d inPosition);
		//might need to change currRoom to roomData again
		bool IsSpaceOutsideMap(const Vector2d inPosition, const RoomData currRoom);
	};
	struct WorldState
	{
		//Need to add camera for tile, not for character
		Vector2d CameraPosition;
		std::vector<ItemData> Items;
		std::vector<EnemyData> Enemies;
		
		float SecondsSincePlayerDefeat;
		std::vector<RoomData> Rooms;
	};


	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState);//, RoomData& roomData);
	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(float deltaSeconds, PlayerState& playerState,WorldState& worldState,RoomData& roomData);//trying to add roomdata. think i need it for inventory.
	void RenderGame(SDL_Renderer* pRenderer,const PlayerState& playerState,const WorldState& worldState);
	void CleanupGame(PlayerState& PlayerState,WorldState& WorldState);
		
	//Do i need to change roomdata to currRoom as it was before? 
	
	//int PositionToIndex(const Position& position, int roomwidth);
}

