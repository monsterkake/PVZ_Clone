#pragma once
#include "patterns.h"
#include "defValues.h"
#include "enemyID.h"
#include "iostream"
#include <SFML\Graphics.hpp>



class Enemy : public HasAnAnimation, public HasACooldown, public HasHitPoints
{
public:
	int line = 0;
	float speed;
	float damage;

	bool canMove = true;
	EnemyID id;
	//void update(float dtAsSeconds, sf::Vector2f target) override {};
	Enemy() 
	{
		animationSpeed = 1;
		id = EnemyID::none;
		speed = BASE_ENEMY_SPEED;
		hp = BASE_ENEMY_HP;
		damage = BASE_ENEMY_DAMAGE;
		setBoundRect(sf::FloatRect(0, 0, 10, TILESIZE));
	}
	virtual void update(float dtAsSeconds) = 0;
	sf::FloatRect getBoundRect() override
	{
		return boundRect;

	} 
	virtual void setLine(int line) 
	{
		this->line = line;
	}
	int getline() 
	{
		return line;
	}
	void allowMoving() 
	{
		canMove = true;
	}
	void disAllowMoving() 
	{
		canMove = false;
	}
	void move(sf::Vector2f position) override
	{
		this->position += position;
		boundRect.left += position.x;
		boundRect.top += position.y;
	}
	void setSpeed(float speed)
	{
		this->speed = speed;
	}
	float getSpeed()
	{
		return speed;
	}
};

class Scout : public Enemy
{
public:
	Scout()
	{
		hp     *=   0.2 ;
		damage *=   0   ;
		speed  *=   2   ;
	}
	void update(float dtAsSeconds) override;
};

class Swarmling : public Enemy
{
public:
	Swarmling()
	{
		hp *= 1;
		damage *= 1;
		speed *= 1;
	}
	void update(float dtAsSeconds) override;
};

class Avoider : public Enemy
{
	bool hasChangedLine = false;
	int newLine = 0;
	float initialPositionY = 0;
public:
	Avoider()
	{
		hp *= 0.7;
		damage *= 2;
		speed *= 1.3;
		maxHp = hp;

		while (newLine == 0)
			newLine = rand() % 3 - 1;
	}
	void update(float dtAsSeconds) override;
	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		boundRect.left = position.x;
		boundRect.top = position.y;
		initialPositionY = position.y;
	}
};

class Lardster : public Enemy
{
public:
	Lardster()
	{
		hp *= 5;
		damage *= 0.2;
		speed *= 0.6;
	}
	void update(float dtAsSeconds) override;
};

class Animuta : public Enemy
{
public:
	Animuta()
	{
		hp *= 2;
		damage *= 0;
		speed *= 1;
	}
	void update(float dtAsSeconds) override;
};

class BigDaddy : public Enemy
{
public:
	BigDaddy()
	{
		hp *= 10;
		damage *= 3;
		speed *= 1;
	}
	void update(float dtAsSeconds) override;
};

class PsychicEmitter : public Enemy
{
public:
	PsychicEmitter()
	{
		hp *= 4;
		damage *= 0;
		speed *= 1;
	}
	void update(float dtAsSeconds) override;
};

class ThreeHundredWatts : public Enemy
{
public:
	ThreeHundredWatts()
	{
		hp *= 5;
		damage *= 1;
		speed *= 0.9;
	}
	void update(float dtAsSeconds) override;
};
