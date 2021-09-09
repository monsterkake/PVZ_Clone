#pragma once
#include "patterns.h"
#include "unitType.h"
#include "enemy.h"
#include "defValues.h"
#include "unit.h"

class UnitContainer 
{
public:
	EnemyContainer enemyContainer;
	std::shared_ptr<Unit> Units[MAX_UNITS];
	UnitContainer() 
	{
		for (int i = 0; i < MAX_UNITS; i++) 
		{
			Units[i] = nullptr;
		}
	}
	void addNew(UnitID id, sf::Vector2f position, sf::Vector2i parentIndex)
	{
		for (int i = 0; i < MAX_UNITS; i++)
		{
			//If element is not occupied
			if (Units[i] == nullptr)
			{
				Units[i] = std::shared_ptr<Unit>(new Fighter);
				switch (id)
				{
				case UnitID::Fighter1:
					Units[i]->setHp(100);
					break;
				default:break;
				}

				Units[i]->id = id;
				Units[i]->setPosition(position);
				Units[i]->parentIndex = parentIndex;
				return;
				
			}
		}
	}
	void destroy(int index)
	{
		Units[index] = nullptr;
	}

	void update(float dtAsSeconds) 
	{
		for (int i = 0; i < MAX_UNITS; i++)
		{
			if (Units[i] != nullptr)
			{
				Units[i]->update(dtAsSeconds,enemyContainer.getClosestEnemy());
			}
		}
		enemyContainer.updateEnemies(dtAsSeconds);
	}
};