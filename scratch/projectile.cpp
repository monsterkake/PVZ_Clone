#include "projectile.h"

void ProjectileContainer::addNew(ProjectileID id, sf::Vector2f position)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element is not occupied
		if (Projectiles[i].id == ProjectileID::none)
		{
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
void ProjectileContainer::moveProjectiles(float dtAsSeconds)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		//If element occupied
		if (Projectiles[i].id != ProjectileID::none)
		{
			Projectiles[i].move(sf::Vector2f(dtAsSeconds * Projectiles[i].speed, 0));
			//Check if it flew off screen
			if (Projectiles[i].getPosition().x > 2000)
			{
				Projectiles[i].id = ProjectileID::none;
			}
		}
	}
}