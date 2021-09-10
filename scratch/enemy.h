#pragma once
#include "patterns.h"
#include "defValues.h"
#include "UnitID.h"
#include "iostream"
#include <SFML\Graphics.hpp>



class Enemy : public Unit
{
public:
	int line = 0;
	float damage;
	bool canMove = true;
	void update(float dtAsSeconds, sf::Vector2f target) override {};
	Enemy() 
	{
		animationSpeed = 1;
		id = UnitID::none;
		speed = BASE_ENEMY_SPEED;
		hp = BASE_ENEMY_HP;
		damage = BASE_ENEMY_DAMAGE;
		setBoundRect(sf::FloatRect(0, 0, 10, TILESIZE));
	}
	sf::FloatRect getBoundRect() override
	{
		return boundRect;

	} 
	void allowMoving() 
	{
		canMove = true;
	}
	void disAllowMoving() 
	{
		canMove = false;
	}
	//void move(sf::Vector2f position) override
	//{
	//	this->position -= position;
	//	boundRect.left += position.x;
	//	boundRect.top += position.y;
	//}
};

