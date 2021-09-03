#pragma once
#include "patterns.h"
#include "defValues.h"
#include "UnitID.h"
#include "iostream"
#include <SFML\Graphics.hpp>

class Enemy : public Unit
{
public:
	int line = 0;
	void update(float dtAsSeconds, sf::Vector2f target) override {};
	Enemy() 
	{
		id = UnitID::none;
		speed = -10.0;
		hp = 100;
		setBoundRect(sf::FloatRect(0, 0, 10, TILESIZE));
	}
};

class EnemyContainer 
{
public:
	Enemy enemy[MAX_ENEMIES];
	int indexOfClosestEnemy = 0;
	int indexOfClosestEnemyInLine[AMOUNT_OF_LINES];
	int amountOfEnemies = 0;
	float spawnCooldown = 0;
	float SpawnRate = 0.5;

	EnemyContainer() 
	{
		for (int i = 0; i < AMOUNT_OF_LINES; i++) 
		{
			indexOfClosestEnemyInLine[i] = 0;
		}
	}

	void spawnEnemies(float dtAsSeconds);

	void addNew(UnitID id, sf::Vector2f position, int line);

	void destroy(int index);

	void updateEnemies(float dtAsSeconds);

	sf::Vector2f getClosestEnemy();
};
