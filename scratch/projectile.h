#pragma once

#include "patterns.h"
#include "defValues.h"
#include "projectileID.h"
#include <iostream>
#include "projectileType.h"
#include "enemy.h"

class Projectile : public HasAnAnimation, public HasRotation
{
protected:
	std::shared_ptr<std::shared_ptr<Enemy>> ptrToClosestEnemy;
public:
	int line = 0;
	ProjectileType type = ProjectileType::none;
	ProjectileID id = ProjectileID::none;
	float speed = 1000.0;
	float damage = 0;
	virtual void update(float dtAsSeconds) = 0;

	Projectile() 
	{
		ptrToClosestEnemy = std::shared_ptr<std::shared_ptr<Enemy>>(new std::shared_ptr<Enemy>);
		*ptrToClosestEnemy = nullptr;
		setBoundRect(sf::FloatRect(0, 0, PROJECTILE_SIZE, PROJECTILE_SIZE));
		
	}
	void setTargetEnemy(std::shared_ptr<Enemy> targetEnemy)
	{
		*ptrToClosestEnemy = targetEnemy;
	}
};

class Bullet : public Projectile
{
public:
	void update(float dtAsSeconds) override;
	Bullet() 
	{
		damage = 10;
		speed = 1000.0;
		type = ProjectileType::Bullet;
	}
};

class Rocket : public Projectile
{
	sf::Vector2f target;
	sf::Vector2f prevPosition;
	bool targetIsDead = false;
public:
	void update(float dtAsSeconds) override;
	Rocket() 
	{
		//setFrameSize(PROJECTILE_SIZE);
		damage = 10;
		type = ProjectileType::Rocket;
		speed = 500.0;
	}
};

class Laser : public Projectile ,public HasACooldown
{
public:
	void update(float dtAsSeconds) override;
	Laser()
	{
		animationSpeed = 0.1;
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

	void addNew(ProjectileID id, sf::Vector2f position,int line, std::shared_ptr<Enemy> ptrToClosestEnemy);

	void destroy(int index);

	void updateProjectiles(float dtAsSeconds);

};
