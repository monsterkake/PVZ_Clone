#include "engine.h"
#include "projectileID.h"
#include "UnitID.h"
#include "defValues.h"
#include "buildingType.h"
#include <iostream>
#include "projectileType.h"

using namespace sf;

//bool spawnEnemies = true;
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

	// income update
	frames++;
	timer -= dtAsSeconds;
	if (timer < 0)
	{
		//Measure FPS
		if (FPSmeasuring)
		{
			std::cout << frames << std::endl;
			frames = 0;
		}
		timer = 1;
		resourseEnergy += baseEnergyIncome;
		resourseMinerals += baseMineralsIncome;

	}



	//move PopUpWindows
	if (researchWindow.isGrabbed())
	{
		sf::Vector2f dpos = mousePosition - savedPressLeftClickLocation;
		researchWindow.setPosition(researchWindow.getOriginalPosition() + dpos);
	}
	//Update PopUpWindows
	researchWindow.update(mousePosition, baseResearchIncome, dtAsSeconds);
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
				if (tileMap.lines[i].tiles[j].building->getHp() < 0)
				{
					tileMap.lines[i].tiles[j].removeBuilding();
				}
				else
				{
					id_action = tileMap.lines[i].tiles[j].building->update(dtAsSeconds);

					if (id_action != ActionID::none)
					{
						// for line - dependant actions
						if (enemyContainer->getClosestEnemyInLine(i) != nullptr)
						{
							switch (id_action)
							{
							case ActionID::ShootProjectile:
								ProjectileContainer.addNew(ProjectileID::Bullet1, tileMap.lines[i].tiles[j].building->getPosition(), i, enemyContainer->getClosestEnemy()); /* i - current line*/
								break;
							case ActionID::ShootLaser:
								if (enemyContainer->getClosestEnemyInLine(i) != nullptr)
									ProjectileContainer.addNew(ProjectileID::Laser1, tileMap.lines[i].tiles[j].building->getPosition(), i, enemyContainer->getClosestEnemy()); /* i - current line*/
								break;
							default:
								break;
							}
						}
						// fore line - independant actions
						if (enemyContainer->getClosestEnemy() != nullptr)
						{
							switch (id_action)
							{
							case ActionID::LaunchRocket:
								ProjectileContainer.addNew(ProjectileID::Rocket1, tileMap.lines[i].tiles[j].building->getPosition(), i, enemyContainer->getClosestEnemy()); /* i - current line*/
								break;
							case ActionID::ReleaseFighter:
								UnitContainer.addNew(UnitID::Fighter1, tileMap.lines[i].tiles[j].building->getPosition(), sf::Vector2i(i, j));
								break;
							default:
								break;
							}
						}
						// for enemy independant actions
						switch (id_action)
						{
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
	}

	ProjectileContainer.updateProjectiles(dtAsSeconds);


	if (spawnEnemies)
	{
		enemyContainer->spawnEnemies(dtAsSeconds);
	}

	//Update Units and Enemies
	UnitContainer.update(dtAsSeconds);

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemyContainer->enemy[i] != nullptr)
		{
			enemyContainer->enemy[i]->allowMoving();
			for (int j = 0; j < TILES_IN_A_LINE; j++)
			{
				if (tileMap.lines[enemyContainer->enemy[i]->line].tiles[j].building != nullptr)
				{
					if (enemyContainer->enemy[i]->getBoundRect().intersects(tileMap.lines[enemyContainer->enemy[i]->line].tiles[j].building->getBoundRect()))
					{
						enemyContainer->enemy[i]->disAllowMoving();
						tileMap.lines[enemyContainer->enemy[i]->line].tiles[j].building->recieveDamage(enemyContainer->enemy[i]->damage * dtAsSeconds);
					}
				}
			}
		}
	}
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
					ProjectileContainer.addNew(ProjectileID::Bullet1, UnitContainer.Units[i]->getPosition(), 0, enemyContainer->getClosestEnemy());
					break;
				default:
					break;
				}
			}
		}
	}
	//Check projectile collisions
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemyContainer->enemy[i] != nullptr)
		{
			for (int j = 0; j < MAX_PROJECTILES; j++)
			{
				if (ProjectileContainer.projectiles[j] != nullptr)
				{
					// if Projectile.type is bullet
					if (ProjectileContainer.projectiles[j]->type == ProjectileType::Bullet)
					{

						if (ProjectileContainer.projectiles[j]->getBoundRect().intersects(enemyContainer->enemy[i]->getBoundRect()))
						{
							enemyContainer->enemy[i]->recieveDamage(ProjectileContainer.projectiles[j]->damage);
							ProjectileContainer.destroy(j);
						}

					}
					else
						// if Projectile type is Rocket
						if (ProjectileContainer.projectiles[j]->type == ProjectileType::Rocket)
						{
							if (ProjectileContainer.projectiles[j]->getBoundRect().intersects(enemyContainer->enemy[i]->getBoundRect()))
							{
								enemyContainer->enemy[i]->recieveDamage(ProjectileContainer.projectiles[j]->damage);
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

				if (enemyContainer->getClosestEnemyInLine(ProjectileContainer.projectiles[i]->line) != nullptr)
				{
					enemyContainer->getClosestEnemyInLine(ProjectileContainer.projectiles[i]->line)->recieveDamage(ProjectileContainer.projectiles[i]->damage);
				}
			}
		}
	}
}