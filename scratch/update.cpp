#include "engine.h"
#include "projectileID.h"
#include "enemyID.h"
#include "defValues.h"
#include "buildingType.h"
#include <iostream>

using namespace sf;

bool spawnEnemies = true;
bool FPSmeasuring = false;

float timer = 1;
int frames = 0; 

void Engine::update(float dtAsSeconds)
{
	if (DebugMode) 
	{
		resourseEnergy = 10000;
		resourseMinerals = 10000;
	}
	//Measure FPS
	if (FPSmeasuring) 
	{
		frames++;
		timer -= dtAsSeconds;
		if (timer < 0) 
		{
			std::cout << frames << std::endl;
			timer = 1;
			frames = 0;
		}
	}

	// Update Buildings
	ProjectileID id_projectile;
	ActionID id_action;
	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j < TILES_Y; j++)
		{
			// if building is turret
			if (tileMap.tiles[i][j].Building.type == BuildingType::turret)
			{
				if (tileMap.tiles[i][j].Building.id != BuildingID::none)
				{

					id_projectile = tileMap.tiles[i][j].Building.update(dtAsSeconds);

					if (id_projectile != ProjectileID::none)
					{

						ProjectileContainer.addNew(id_projectile, tileMap.tiles[i][j].Building.getPosition());
					}
				}
			}
			else
			{
				// if building is economy
				if (tileMap.tiles[i][j].Building.type == BuildingType::economy)
				{

					if (tileMap.tiles[i][j].Building.id != BuildingID::none)
					{
						id_action = tileMap.tiles[i][j].Building.act(dtAsSeconds);

						if (id_action != ActionID::none)
						{
							switch (id_action)
							{
							case ActionID::a0:
								resourseEnergy += 1;
								break;
							case ActionID::a1:
								resourseMinerals += 1;
								break;
							case ActionID::a2:
								break;
							case ActionID::a3:
								break;
							case ActionID::a4:
								break;
							default:
								break;
							}

						}
					}
				}
			}
		}
	}
	//Update Projectiles
	ProjectileContainer.moveProjectiles(dtAsSeconds);


	if (spawnEnemies)
	{
		//spawnEnemies = false;
		EnemyContainer.spawnEnemies(dtAsSeconds);
		//EnemyContainer.addNew(EnemyID::e0, sf::Vector2f(1800, 500));
	}

	//Update Enemies
	EnemyContainer.updateEnemies(dtAsSeconds);
	//Check collisions
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (EnemyContainer.enemy[i].id != EnemyID::none)
		{
			for (int j = 0; j < MAX_PROJECTILES; j++)
			{
				if (ProjectileContainer.Projectiles[j].id != ProjectileID::none)
				{

					if (ProjectileContainer.Projectiles[j].getBoundRect().intersects(EnemyContainer.enemy[i].getBoundRect()))
					{
						ProjectileContainer.Projectiles[j].id = ProjectileID::none;
						EnemyContainer.enemy[i].hp -= ProjectileContainer.Projectiles[j].damage;
					}
				}
			}
		}
	}
}