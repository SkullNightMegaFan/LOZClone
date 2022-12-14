#pragma once
#include "Sprite.h"
//completely done
namespace DungeonGame
{
	class Enemy : public Sprite
	{
	public:

		void SetEnemyIndex(int newIndex);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);// WorldState& worldState);


	private:
		int EnemyIndex;
	};
}
