#include "projectile.h"
#include <math.h>
#include <iostream>

bool ProjectileContainer::canAddNewFighter()
{

	if (hangarCapacity >= amountOfFighters + 1)
	{
		amountOfFighters += 1;
		return true;
	}
	else
		return false;

}

void ProjectileContainer::addHangar()
{
	hangarCapacity++;
}

void ProjectileContainer::removehangar()
{
	hangarCapacity--;
}

void ProjectileContainer::addNew(ProjectileID id, sf::Vector2f position, int line)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element is not occupied
		if (Projectiles[i].id == ProjectileID::none)
		{
			//setType
			if (ProjectileID::p0 <= id && id <= ProjectileID::p7)
			{
				Projectiles[i].speed = 1000.0;
				Projectiles[i].type = ProjectileType::Bullet;
			}


			if (id == ProjectileID::Rocket1)
			{
				Projectiles[i].type = ProjectileType::Rocket;
				Projectiles[i].speed = 500.0;

			}
			if (id == ProjectileID::Fighter1)
			{
				if (!canAddNewFighter())
					return;

				Projectiles[i].type = ProjectileType::Fighter;
				Projectiles[i].speed = 1000.0;
			}

			Projectiles[i].line = line;
			Projectiles[i].id = id;
			Projectiles[i].setPosition(position);
			Projectiles[i].getTexture().setOrigin(Projectiles[i].getTexture().getSize());
			Projectiles[i].damage = 10;
			projectileAmount++;
			return;
		}

	}
}

void ProjectileContainer::destroy(int index)
{
	Projectiles[index].id = ProjectileID::none;
	projectileAmount--;
}

void ProjectileContainer::moveProjectiles(float dtAsSeconds, sf::Vector2f target)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element occupied
		if (Projectiles[i].id != ProjectileID::none)
		{
			if (Projectiles[i].type == ProjectileType::Bullet)
			{
				Projectiles[i].move(sf::Vector2f(dtAsSeconds * Projectiles[i].speed, 0));
				//Check if it flew off screen
				if (Projectiles[i].getPosition().x > (SPAWN_DISTANCE + TILESIZE * TILES_IN_A_LINE))
				{
					Projectiles[i].id = ProjectileID::none;
				}
			}
			if (Projectiles[i].type == ProjectileType::Rocket)
			{
				float dx = Projectiles[i].speed * cosf((target.y - Projectiles[i].getPosition().y) /
					(sqrt(
						pow(
							target.x - Projectiles[i].getPosition().x, 2)
						+ pow(
							target.y - Projectiles[i].getPosition().y, 2))));
				float dy = sqrt(pow(Projectiles[i].speed, 2) - pow(dx, 2));

				if (target.y - Projectiles[i].getPosition().y < 0)
				{
					dy *= -1;
				}
				if (target.x - Projectiles[i].getPosition().x < 0)
				{
					dx *= -1;
				}


				Projectiles[i].move(sf::Vector2f(dtAsSeconds * dx, dtAsSeconds * dy));
			}
			if (Projectiles[i].type == ProjectileType::Fighter)
			{
				sf::Vector2f attackPosition;
				attackPosition.x = target.x - FIGHTER_ATTACK_DISTANCE + rand() % 10 - 5;
				attackPosition.y = target.y + rand() % 10 - 5;

				float dx = Projectiles[i].speed;
				float dy = Projectiles[i].speed;

				if (attackPosition.y - Projectiles[i].getPosition().y < 0)
				{
					dy *= -1;
				}
				if (attackPosition.x - Projectiles[i].getPosition().x < 0)
				{
					dx *= -1;
				}

				Projectiles[i].move(sf::Vector2f(dtAsSeconds * dx, dtAsSeconds * dy));
			}
		}
	}
}
