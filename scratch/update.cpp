#include "engine.h"
#include "projectileID.h"
#include "UnitID.h"
#include "defValues.h"
#include "buildingType.h"
#include <iostream>
#include "projectileType.h"

using namespace sf;

bool spawnEnemies = true;
bool FPSmeasuring = true;

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
	for (int i = 0; i < AMOUNT_OF_LINES; i++)
	{
		for (int j = 0; j < TILES_IN_A_LINE; j++)
		{
			// if building exists
			if (tileMap.lines[i].tiles[j].building != nullptr)
			{

				id_action = tileMap.lines[i].tiles[j].building->update(dtAsSeconds);

				if (id_action != ActionID::none)
				{
					switch (id_action)
					{
					case ActionID::ShootProjectile:
						ProjectileContainer.addNew(ProjectileID::Bullet1, tileMap.lines[i].tiles[j].building->getPosition(), i); /* i - current line*/
						break;
					case ActionID::LaunchRocket:
						ProjectileContainer.addNew(ProjectileID::Rocket1, tileMap.lines[i].tiles[j].building->getPosition(), i); /* i - current line*/
						break;
					case ActionID::ReleaseFighter:
						UnitContainer.addNew(UnitID::Fighter1, tileMap.lines[i].tiles[j].building->getPosition());
						break;
					case ActionID::ShootLaser:
						ProjectileContainer.addNew(ProjectileID::Laser1, tileMap.lines[i].tiles[j].building->getPosition(), i); /* i - current line*/
						break;
					case ActionID::ProduceEnergy:
						resourseEnergy++;
						break;
					case ActionID::ProduceMinerals:
						resourseMinerals++;
						break;
					default:
						break;
					}
					
				}

			}
		}
	}
	//Update Projectiles
	ProjectileContainer.updateProjectiles(dtAsSeconds , UnitContainer.enemyContainer.getClosestEnemy());

	if (spawnEnemies)
	{
		//spawnEnemies = false;
		UnitContainer.enemyContainer.spawnEnemies(dtAsSeconds);
		//EnemyContainer.addNew(UnitID::e0, sf::Vector2f(1800, 500));
	}

	//Update Units and Enemies
	UnitContainer.update(dtAsSeconds);
	// Process fighter shooting
	for (int i = 0; i < MAX_UNITS; i++) 
	{
		if (UnitContainer.Units[i] != nullptr) 
		{
			if (UnitContainer.Units[i]->isReadyToFire())
			{
				switch (UnitContainer.Units[i]->id)
				{
				case UnitID::Fighter1:
					ProjectileContainer.addNew(ProjectileID::Bullet1, UnitContainer.Units[i]->getPosition(), 0);
					break;
				default:
					break;
				}
			}
		}
	}
	//Check collisions
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (UnitContainer.enemyContainer.enemy[i].id != UnitID::none)
		{
			for (int j = 0; j < MAX_PROJECTILES; j++)
			{
				if (ProjectileContainer.projectiles[j] != nullptr)
				{
					// if Projectile.type is bullet
					if (ProjectileContainer.projectiles[j]->type == ProjectileType::Bullet) 
					{
						// if They are on the same line
						//if (ProjectileContainer.Projectiles[j].line == EnemyContainer.enemy[i].line) 
						//{
							if (ProjectileContainer.projectiles[j]->getBoundRect().intersects(UnitContainer.enemyContainer.enemy[i].getBoundRect()))
							{

								UnitContainer.enemyContainer.enemy[i].recieveDamage(ProjectileContainer.projectiles[j]->damage);
								ProjectileContainer.destroy(j);
	
							}
						//}
						
					}
					else
						// if Projectile type is Rocket
						if (ProjectileContainer.projectiles[j]->type == ProjectileType::Rocket)
						{
							if (ProjectileContainer.projectiles[j]->getBoundRect().intersects(UnitContainer.enemyContainer.enemy[i].getBoundRect()))
							{
								UnitContainer.enemyContainer.enemy[i].recieveDamage(ProjectileContainer.projectiles[j]->damage);
								ProjectileContainer.destroy(j);
							}
						}	
				}
			}
		}
	}
	// Check Laser hits
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (ProjectileContainer.projectiles[i] != nullptr) 
		{
			if (ProjectileContainer.projectiles[i]->type == ProjectileType::Laser)
			{
				UnitContainer.enemyContainer.enemy[
					UnitContainer.enemyContainer.indexOfClosestEnemyInLine[
						ProjectileContainer.projectiles[i]->line]].recieveDamage(ProjectileContainer.projectiles[i]->damage);
			}
		}
	}
}