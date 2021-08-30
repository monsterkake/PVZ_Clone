#include "enemy.h"



void EnemyContainer::spawnEnemies(float dtAsSeconds)
{
	spawnCooldown -= dtAsSeconds;
	if (spawnCooldown < 0)
	{
		spawnCooldown = SpawnRate;

		addNew(EnemyID::e0, sf::Vector2f(TILES_X * TILESIZE + SPAWN_DISTANCE, (rand() % TILES_Y) * TILESIZE + TILEMAP_POSITION_Y));
	}
}

void EnemyContainer::addNew(EnemyID id, sf::Vector2f position)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element is not occupied
		if (enemy[i].id == EnemyID::none)
		{
			enemy[i].id = id;
			enemy[i].setPosition(position);
			amountOfEnemies++;
			switch (id)
			{
			case EnemyID::e0:
				enemy[i].hp = 100;
				break;
			default:break;
			}
			return;
		}
	}
}

void EnemyContainer::destroy(int index)
{
	enemy[index].id = EnemyID::none;
	amountOfEnemies--;
}

void EnemyContainer::updateEnemies(float dtAsSeconds)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element occupied
		if (enemy[i].id != EnemyID::none)
		{
			if (enemy[i].hp < 0)
				destroy(i);
			else
			{
				enemy[i].move(sf::Vector2f(dtAsSeconds * enemy[i].speed, 0));
				enemy[i].updateAnimation(dtAsSeconds);
			}

		}
	}
}