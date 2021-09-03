#include "enemy.h"



void EnemyContainer::spawnEnemies(float dtAsSeconds)
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

void EnemyContainer::addNew(UnitID id, sf::Vector2f position, int line)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element is not occupied
		if (enemy[i].id == UnitID::none)
		{
			indexOfClosestEnemyInLine[line] = i;
			enemy[i].line = line;
			enemy[i].id = id;
			enemy[i].setPosition(position);
			amountOfEnemies++;
			switch (id)
			{
			case UnitID::e0:
				enemy[i].setHp(100);
				break;
			default:break;
			}
			return;
		}
	}
}

void EnemyContainer::destroy(int index)
{
	enemy[index].id = UnitID::none;
	enemy[index].setPosition(sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE, 0));
	amountOfEnemies--;
}

void EnemyContainer::updateEnemies(float dtAsSeconds)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element is occupied
		if (enemy[i].id != UnitID::none)
		{
			if (enemy[indexOfClosestEnemy].getPosition().x > enemy[i].getPosition().x)
			{
				indexOfClosestEnemy = i;
			}
			if (enemy [ indexOfClosestEnemyInLine [ enemy[i].line ] ].getPosition().x > enemy[i].getPosition().x) 
			{
				indexOfClosestEnemyInLine[enemy[i].line] = i;
			}

			if (enemy[i].getHp() < 0)
				destroy(i);
			else
			{
				enemy[i].move(sf::Vector2f(dtAsSeconds * enemy[i].getSpeed(), 0));
				enemy[i].updateAnimation(dtAsSeconds);
			}

		}
	}
}

sf::Vector2f EnemyContainer::getClosestEnemy()
{
	return enemy[indexOfClosestEnemy].getPosition();
}

