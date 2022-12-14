#pragma once
#include "Sprite.h"
//completely done
namespace DungeonGame
{
	class Items : public Sprite
	{
	public:

		void SetItemIndex(int newIndex);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);// WorldState& worldState);


	private:
		int itemIndex;
	};
}
