#include "projectile.h"
#include <math.h>
#include <iostream>

void ProjectileContainer::addNew(ProjectileID id, sf::Vector2f position, int line)
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

void ProjectileContainer::updateProjectiles(float dtAsSeconds, sf::Vector2f target)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element occupied
		if (projectiles[i] != nullptr)
		{
			projectiles[i]->update(dtAsSeconds, target);

			if (projectiles[i]->id == ProjectileID::none)
			{
				destroy(i);
			}
		}
	}
}

void Bullet::update(float dtAsSeconds, sf::Vector2f target)
{
	updateAnimation(dtAsSeconds);
	move(sf::Vector2f(dtAsSeconds * speed, 0));
	//Check if it flew off screen
	if (position.x > (SPAWN_DISTANCE + TILESIZE * TILES_IN_A_LINE))
	{
		id = ProjectileID::none;
	}
}

void Rocket::update(float dtAsSeconds, sf::Vector2f target)
{
	updateAnimation(dtAsSeconds);
	float cos_;
	cos_ = cosf((target.y  - position.y) /
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
}

void Laser::update(float dtAsSeconds, sf::Vector2f target)
{
	updateAnimation(dtAsSeconds);
	damage = 100.0 * dtAsSeconds;
	//damage = 10.0 * dtAsSeconds;
	if (cooldownIsReady(dtAsSeconds))
	{
		id = ProjectileID::none;
		
	}
	
}
