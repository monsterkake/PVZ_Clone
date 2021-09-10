#pragma once
#include "enemy.h"
#include "defValues.h"

class EnemyContainer
{
public:
	std::shared_ptr<Enemy> enemy[MAX_ENEMIES];
	std::shared_ptr<Enemy> ClosestEnemy = nullptr;
	std::shared_ptr<Enemy> ClosestEnemyInLine[AMOUNT_OF_LINES];
	int amountOfEnemies = 0;
	float spawnCooldown = 0;
	float SpawnRate = 0.5;

	EnemyContainer()
	{
		for (int i = 0; i < AMOUNT_OF_LINES; i++)
		{
			ClosestEnemyInLine[i] = nullptr;
		}
		for (int i = 0; i < MAX_ENEMIES; i++) 
		{
			enemy[i] = nullptr;
		}
	}

	void spawnEnemies(float dtAsSeconds)
	{
		spawnCooldown -= dtAsSeconds;
		if (spawnCooldown < 0)
		{
			spawnCooldown = SpawnRate;

			auto randomline = (rand() % AMOUNT_OF_LINES);

			addNew(UnitID::e0, sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE,
				randomline * TILESIZE + TILEMAP_POSITION_Y),
				randomline);

		}
	}

	void addNew(UnitID id, sf::Vector2f position, int line)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			//If element is not occupied
			if (enemy[i] == nullptr)
			{
				enemy[i] = std::shared_ptr<Enemy>(new Enemy);
				if(ClosestEnemyInLine[line] == nullptr)
					ClosestEnemyInLine[line] = enemy[i];
				if (ClosestEnemy == nullptr)
					ClosestEnemy = enemy[i];
				enemy[i]->line = line;
				enemy[i]->id = id;
				enemy[i]->setPosition(position);
				amountOfEnemies++;
				switch (id)
				{
				case UnitID::e0:
					enemy[i]->setHp(100);
					break;
				default:break;
				}
				return;
			}
		}
	}

	void destroy(int index)
	{
		if (enemy[index] == ClosestEnemy)
			ClosestEnemy = nullptr;
		
		if (enemy[index] == ClosestEnemyInLine[enemy[index]->line])
			ClosestEnemyInLine[enemy[index]->line] = nullptr;

		enemy[index] = nullptr;
		amountOfEnemies--;
	}

	void updateEnemies(float dtAsSeconds)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			//If element is occupied
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->getHp() < 0) 
				{
					destroy(i);
				}
				else
				{
					if (enemy[i]->canMove)
					{
						enemy[i]->move(sf::Vector2f(dtAsSeconds * enemy[i]->getSpeed(), 0));
					}
					enemy[i]->updateAnimation(dtAsSeconds);
				
					if (ClosestEnemy == nullptr) 
					{
						ClosestEnemy = enemy[i];
					}
					else 
					{
						if (ClosestEnemy->getPosition().x > enemy[i]->getPosition().x)
						{
							ClosestEnemy = enemy[i];
						}
					}
					
					if (ClosestEnemyInLine[enemy[i]->line] == nullptr)
					{
						ClosestEnemyInLine[enemy[i]->line] = enemy[i];
					}
					else 
					{
						if (ClosestEnemyInLine[enemy[i]->line]->getPosition().x > enemy[i]->getPosition().x)
						{
							ClosestEnemyInLine[enemy[i]->line] = enemy[i];
						}
					}
					
				}
				
			}
		}
	}
	std::shared_ptr<Enemy> getClosestEnemy()
	{
		return ClosestEnemy;
	}
	std::shared_ptr<Enemy> getClosestEnemyInLine(int index)
	{
		return ClosestEnemyInLine[index];
	}
};