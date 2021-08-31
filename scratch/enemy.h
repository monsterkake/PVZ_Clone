#pragma once
#include "patterns.h"
#include "defValues.h"
#include "enemyID.h"
#include "iostream"
#include <SFML\Graphics.hpp>

class Enemy : public HasAnAnimation
{
public:
	int line = 0;
	EnemyID id = EnemyID::none;
	float speed = -10.0;
	float hp = 100;
	Enemy() 
	{
		setBoundRect(sf::FloatRect(0, 0, 10, TILESIZE));
	}
};

class EnemyContainer 
{
public:
	Enemy enemy[MAX_ENEMIES];
	int indexOfClosestEnemy = 0;
	int amountOfEnemies = 0;
	float spawnCooldown = 0;
	float SpawnRate = 0.5;
	void spawnEnemies(float dtAsSeconds);

	void addNew(EnemyID id, sf::Vector2f position, int line);

	void destroy(int index);

	void updateEnemies(float dtAsSeconds);

	sf::Vector2f getClosestEnemy();
};
