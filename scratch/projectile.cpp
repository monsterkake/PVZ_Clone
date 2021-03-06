#include "projectile.h"
#include <math.h>
#include <iostream>

void ProjectileContainer::addNew(ProjectileID id, sf::Vector2f position, int line, std::shared_ptr<Enemy> ptrToClosestEnemy)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element is not occupied
		if (projectiles[i] == nullptr)
		{
			//setType
			if (ProjectileID::Bullet1 <= id && id <= ProjectileID::p7)
			{
				projectiles[i] = std::shared_ptr<Projectile>(new Bullet);
			}

			if (id == ProjectileID::Rocket1)
			{
				projectiles[i] = std::shared_ptr<Projectile>(new Rocket);
				projectiles[i]->setTargetEnemy(ptrToClosestEnemy);
			}
			if (id == ProjectileID::Laser1)
			{
				projectiles[i] = std::shared_ptr<Projectile>(new Laser);
			}

			projectiles[i]->line = line;
			projectiles[i]->id = id;
			projectiles[i]->setPosition(position);
			//projectiles[i]->damage = 10;
			projectileAmount++;
			return;
		}

	}
}

void ProjectileContainer::destroy(int index)
{
	projectiles[index] = nullptr;
	projectileAmount--;
}

void ProjectileContainer::updateProjectiles(float dtAsSeconds)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element occupied
		if (projectiles[i] != nullptr)
		{
			projectiles[i]->update(dtAsSeconds);

			if (projectiles[i]->id == ProjectileID::none)
			{
				destroy(i);
			}
		}
	}
}

void Bullet::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	move(sf::Vector2f(dtAsSeconds * speed, 0));
	//Check if it flew off screen
	if (position.x > (SPAWN_DISTANCE + TILESIZE * TILES_IN_A_LINE))
	{
		id = ProjectileID::none;
	}
}

void Rocket::update(float dtAsSeconds)
{
	
	updateAnimation(dtAsSeconds);
	if (ptrToClosestEnemy.get()->get()->getHp() <= 0) 
	{
		targetIsDead = true;
	}

	if (!targetIsDead)
	{
		target = ptrToClosestEnemy.get()->get()->getPosition();
	}
	else
	{
		target += sf::Vector2f(2 * (position.x - prevPosition.x), 2 * (position.y - prevPosition.y));
	}

	prevPosition = position;

	float cos_;
	cos_ = cosf(float(target.y  - position.y) /
		(sqrt(
			pow(
				target.x - position.x, 2)
			+ pow(
				target.y  - position.y, 2))));
	
	angle = acosf(cos_) * 100;

	float dx = speed * cos_;

	float dy = sqrt(pow(speed, 2) - pow(dx, 2));

	if (target.y - position.y < 0)
	{
		dy *= -1;
		angle *= -1;
	}
	if (target.x - position.x < 0)
	{
		dx *= -1;
		angle *= -1;
	}


	move(sf::Vector2f(dtAsSeconds * dx, dtAsSeconds * dy));

	//Check if it flew off screen
	if (position.x > (SPAWN_DISTANCE + TILESIZE * TILES_IN_A_LINE))
	{
		id = ProjectileID::none;
	}
	if (position.x < 0 - 500)
	{
		id = ProjectileID::none;
	}
	if (position.y > (SPAWN_DISTANCE + TILESIZE * TILES_IN_A_LINE))
	{
		id = ProjectileID::none;
	}
	if (position.y < 0 - 500)
	{
		id = ProjectileID::none;
	}
}

void Laser::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	damage = 100.0 * dtAsSeconds;
	//damage = 10.0 * dtAsSeconds;
	if (cooldownIsReady(dtAsSeconds))
	{
		id = ProjectileID::none;
		
	}
	
}
