#pragma once

#include "patterns.h"
#include "defValues.h"
#include "projectileID.h"
#include <iostream>

class Projectile : public HasACollision 
{
public:
	
	ProjectileID id = ProjectileID::none;
	float speed = 1000.0;
	float damage = 0;
	Projectile() 
	{
		texture->setFillColor(sf::Color::Blue);
		texture->setOutlineColor(sf::Color::Black);
		texture->setOutlineThickness(1);
		texture->setSize(sf::Vector2f(30, 30));
		setBoundRect(sf::FloatRect(0, 0, 30, 30));
	}
};

class ProjectileContainer 
{
public:
	Projectile Projectiles[MAX_PROJECTILES];
	int projectileAmount = 0;
	ProjectileContainer() 
	{

	}
	void addNew(ProjectileID id, sf::Vector2f position);

	void destroy(int index);

	void moveProjectiles(float dtAsSeconds);

};
