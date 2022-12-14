#include "Items.h"
#include <vector>
#include <string>
#include "Windows.h"

//complete
using namespace DungeonGame;
void Items::SetItemIndex(int newIndex)
{
	itemIndex = newIndex;

}
void Items::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)//,WorldState& worldState)
{
	Vector2d direction(0.0f, 0.0f);
	//I will later set this to the starting position variable


	ItemData& currItem = worldState.Items[itemIndex];
	Vector2d  vecToPlayer = currItem.Position - playerState.PlayerPosition;
	if (currItem.Alive)
	{
		if (vecToPlayer.GetLength() < 30.0f)
		{
			if (currItem.Type == Item_Heart)
			{
				currItem.Alive = false;
				playerState.PlayerHP++;
				playerState.ObtainingItem = true;
				//Next patch i will include music.
				//PlaySound("Assests/LegendOfZeldaSprites/Sound/LOZ_Get_Heart.wav", NULL, SND_SYNC);
			}
			else
			{
				currItem.Alive = false;
				playerState.ItemInventory.push_back(currItem.Type);
				playerState.ObtainingItem = true;
			}
		
		
		}
	}

	Position = currItem.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	visible = currItem.Alive;
}