#include "Enemy.h"
#include <vector>

//complete
using namespace DungeonGame;

void Enemy::SetEnemyIndex(int newIndex)
{
	EnemyIndex = newIndex;

}
void Enemy::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)//,WorldState& worldState)
{
	
	//I will later set this to the starting position variable
	const float Enememy_Movement_Speed = 150.0f;

	EnemyData& currEnemy = worldState.Enemies[EnemyIndex];
	
	if (currEnemy.Alive)// && !playerState.PlayerHasWon())
	{
		Vector2d  vecToPlayer = currEnemy.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 20.0f)
		{
		
			
			if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				//player needs to take damage
				playerState.PlayerHP -= 1;
				playerState.InvincibilitySeconds = 1.5f;
				playerState.PlayerPosition -= Vector2d(90.0, 0.0f);
				//player is now in a hurt state and plays hurt animation
				// while player is invincible play hurt animation
			}
			
		
			/*if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				playerState.PlayerHP -= 1;
				playerState.InvincibilitySeconds = 1.5f;
			}*/
		
		}

		vecToPlayer.Normalize();
		vecToPlayer *= -1.0f;
		currEnemy.Position += vecToPlayer * Enememy_Movement_Speed * deltaSeconds;
	}

	Position = currEnemy.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.85f);
	visible = currEnemy.Alive;
}