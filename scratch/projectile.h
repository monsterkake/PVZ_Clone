#pragma once

#include "patterns.h"
#include "defValues.h"
#include "projectileID.h"
#include <iostream>
#include "projectileType.h"

class Projectile : public HasACollision 
{
protected:

public:
	int line = 0;
	ProjectileType type = ProjectileType::none;
	ProjectileID id = ProjectileID::none;
	float speed = 1000.0;
	float damage = 0;
	virtual void update(float dtAsSeconds, sf::Vector2f target) = 0;

	Projectile() 
	{
		setBoundRect(sf::FloatRect(0, 0, 30, 30));
	}
};

class Bullet : public Projectile
{
public:
	void update(float dtAsSeconds, sf::Vector2f target) override;
	Bullet() 
	{
		damage = 10;
		speed = 1000.0;
		type = ProjectileType::Bullet;
	}
};

class Rocket : public Projectile
{
public:
	void update(float dtAsSeconds, sf::Vector2f target) override;
	Rocket() 
	{
		damage = 10;
		type = ProjectileType::Rocket;
		speed = 500.0;
	}
};

class Laser : public Projectile ,public HasACooldown
{
public:
	void update(float dtAsSeconds, sf::Vector2f target) override;
	Laser()
	{
		damage = 10;
		type = ProjectileType::Laser;
		speed = 0.0;
	}
};

class ProjectileContainer 
{
public:
	std::shared_ptr<Projectile> projectiles[MAX_PROJECTILES];

	int projectileAmount = 0;

	ProjectileContainer() 
	{
		for (int i = 0; i < MAX_PROJECTILES; i++) 
		{
			projectiles[i] = nullptr;
		}
		
	}

	void addNew(ProjectileID id, sf::Vector2f position,int line);

	void destroy(int index);

	void updateProjectiles(float dtAsSeconds, sf::Vector2f target);

};
