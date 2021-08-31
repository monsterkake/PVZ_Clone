#include "enemy.h"



void EnemyContainer::spawnEnemies(float dtAsSeconds)
{
	spawnCooldown -= dtAsSeconds;
	if (spawnCooldown < 0)
	{
		spawnCooldown = SpawnRate;

		auto randomline = (rand() % AMOUNT_OF_LINES);

		addNew(EnemyID::e0, sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE,
			randomline * TILESIZE + TILEMAP_POSITION_Y),
			randomline);
		
	}
}

void EnemyContainer::addNew(EnemyID id, sf::Vector2f position, int line)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element is not occupied
		if (enemy[i].id == EnemyID::none)
		{
			enemy[i].line = line;
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
	//if (index == indexOfClosestEnemy) 
	//{
	//	for (int i = 0; i < MAX_ENEMIES; i++)
	//	{
	//		if(enemy[i].id != EnemyID::none)
	//			if (enemy[indexOfClosestEnemy].getPosition().x > enemy[i].getPosition().x)
	//			{
	//				indexOfClosestEnemy = i;
	//			}
	//	}

	//}
	enemy[index].setPosition(sf::Vector2f(TILES_IN_A_LINE * TILESIZE + SPAWN_DISTANCE, 0));
	amountOfEnemies--;
}

void EnemyContainer::updateEnemies(float dtAsSeconds)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//If element occupied
		if (enemy[i].id != EnemyID::none)
		{
			if (enemy[indexOfClosestEnemy].getPosition().x > enemy[i].getPosition().x)
			{
				indexOfClosestEnemy = i;
			}
			if (enemy[i].hp < 0)
				destroy(i);
			else
			{
				enemy[i].move(sf::Vector2f(dtAsSeconds * enemy[i].speed, 0));
				enemy[i].updateAnimation(dtAsSeconds);
				
			}

		}


		//std::cout << indexOfClosestEnemy << std::endl;
	}
}

sf::Vector2f EnemyContainer::getClosestEnemy()
{
	return enemy[indexOfClosestEnemy].getPosition();
}

