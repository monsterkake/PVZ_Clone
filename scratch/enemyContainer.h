#pragma once
#include "enemy.h"
#include "defValues.h"
#include "enemyID.h"

class EnemyContainer 
{
public:
	std::shared_ptr<Enemy> enemy[MAX_ENEMIES];
	std::shared_ptr<Enemy> ClosestEnemy = nullptr;
	std::shared_ptr<Enemy> ClosestEnemyInLine[AMOUNT_OF_LINES];
	int amountOfEnemies = 0;
	float spawnCooldown = 0;
	float SpawnRate = 0.5;
	int size = MAX_ENEMIES;
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

	bool allowSpawn = false;

	void spawnEnemies(float dtAsSeconds)
	{
		spawnCooldown -= dtAsSeconds;
		if (spawnCooldown < 0)
		{
			spawnCooldown = SpawnRate;

			auto randomline = (rand() % AMOUNT_OF_LINES);
			if (allowSpawn) 
			{
				allowSpawn = false;
				addNew(EnemyID::BigDaddy, sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE,
					randomline * TILESIZE + TILEMAP_POSITION_Y),
					randomline);
			}
			addNew(EnemyID::Swarmling, sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE,
				randomline * TILESIZE + TILEMAP_POSITION_Y),
				randomline);
			
		}
	}

	void addNew(EnemyID id, sf::Vector2f position, int line)
	{
		//EnemyID savedId = id;
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			//If element is not occupied
			if (enemy[i] == nullptr)
			{
				switch (id)
				{
				case EnemyID::none:
					return;
				case EnemyID::Scout:
					enemy[i] = std::shared_ptr<Enemy>(new Scout);
					break;
				case EnemyID::Swarmling:
					enemy[i] = std::shared_ptr<Enemy>(new Swarmling);
					break;
				case EnemyID::Avoider:
					enemy[i] = std::shared_ptr<Enemy>(new Avoider);
					break;
				case EnemyID::Lardster:
					enemy[i] = std::shared_ptr<Enemy>(new Lardster);
					break;
				case EnemyID::Animuta:
					enemy[i] = std::shared_ptr<Enemy>(new Animuta);
					break;
				case EnemyID::BigDaddy:
					enemy[i] = std::shared_ptr<Enemy>(new BigDaddy);
					break;
				case EnemyID::PsychicEmitter:
					//enemy[i] = std::shared_ptr<Enemy>(new PsychicEmitter);
					break;
				case EnemyID::ThreeHundredWatts:
					//enemy[i] = std::shared_ptr<Enemy>(new ThreeHundredWatts);
					break;
				case EnemyID::Symbyont:
					//enemy[i] = std::shared_ptr<Enemy>(new Symbyont);
					break;
				case EnemyID::YoungQueen:
					break;
				case EnemyID::Ravager:
					break;
				case EnemyID::Infestor:
					break;
				case EnemyID::SaltRunner:
					break;
				case EnemyID::NestedLardster:
					break;
				case EnemyID::CumSpreader:
					break;
				case EnemyID::GigaMuta:
					break;
				default:
					break;
				}
				
				if(ClosestEnemyInLine[line] == nullptr)
					ClosestEnemyInLine[line] = enemy[i];
				if (ClosestEnemy == nullptr)
					ClosestEnemy = enemy[i];
				enemy[i]->setLine(line);
				//enemy[i]->id = id;
				
				enemy[i]->setPosition(position);
				amountOfEnemies++;
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
		for (int i = 0; i < AMOUNT_OF_LINES; i++)
		{
			ClosestEnemyInLine[i] = nullptr;
		}

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			//If element is occupied
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->getHp() <= 0) 
				{
					destroy(i);
				}
				else
				{
					enemy[i]->update(dtAsSeconds, enemy, size);

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