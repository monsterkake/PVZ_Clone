#pragma once
#include "patterns.h"
#include "defValues.h"
#include "enemyID.h"
#include <iostream>
#include <SFML\Graphics.hpp>



class Enemy : public HasAnAnimation, public HasACooldown, public HasHitPoints
{
public:
	int line = 0;
	float speed;
	float damage;
	bool canMove = true;
	EnemyID id;
	Enemy() 
	{
		animationSpeed = 1;
		id = EnemyID::none;
		speed = BASE_ENEMY_SPEED;
		hp = BASE_ENEMY_HP;
		damage = BASE_ENEMY_DAMAGE;
		setBoundRect(sf::FloatRect(0, 0, TILESIZE, TILESIZE));
	}
	virtual void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) = 0;
	sf::FloatRect getBoundRect() override
	{
		/*return sf::FloatRect( boundRect.left + TILESIZE/4, 
			boundRect.top + TILESIZE / 4,
			boundRect.width - TILESIZE / 4,
			boundRect.height - TILESIZE / 4);*/
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
		this->position -= position;
		boundRect.left -= position.x;
		boundRect.top -= position.y;
	}
	void setSpeed(float speed)
	{
		this->speed = speed;
	}
	float getSpeed()
	{
		return speed;
	}
	void onUpdate(float dtAsSeconds)
	{
		updateAnimation(dtAsSeconds);
		if (canMove)
		{
			move(sf::Vector2f(dtAsSeconds * speed, 0));
		}
	}
};

class Scout : public Enemy
{
public:
	Scout()
	{
		id = EnemyID::Scout;
		hp     *=   0.2 ;
		maxHp = hp;
		damage *=   0   ;
		speed  *=   2   ;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
};

class Swarmling : public Enemy
{
public:
	Swarmling()
	{
		id = EnemyID::Swarmling;
		hp *= 1;
		maxHp = hp;
		damage *= 1;
		speed *= 1;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
};

class Avoider : public Enemy
{
	bool hasChangedLine = false;
	int newLine = 0;
	float initialPositionY = 0;
public:
	Avoider()
	{
		id = EnemyID::Avoider;
		hp *= 0.7;
		maxHp = hp;
		damage *= 2;
		speed *= 1.3;
		maxHp = hp;

		while (newLine == 0)
			newLine = rand() % 3 - 1;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
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
		id = EnemyID::Lardster;
		hp *= 5;
		maxHp = hp;
		damage *= 0.2;
		speed *= 0.6;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
};

class Animuta : public Enemy
{
public:
	sf::FloatRect areaOfeffect = sf::FloatRect(0,0,TILESIZE*3, TILESIZE * 3);
	Animuta()
	{
		cooldown = 1;
		actionSpeed = 5;
		id = EnemyID::Animuta;
		hp *= 2;
		maxHp = hp;
		damage *= 0;
		speed *= 1;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
	void move(sf::Vector2f position) override
	{
		this->position -= position;
		boundRect.left -= position.x;
		boundRect.top -= position.y;
		areaOfeffect.left -= position.x;
		areaOfeffect.top -= position.y;
	}
	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		boundRect.left = position.x;
		boundRect.top = position.y;
		areaOfeffect.left = position.x - TILESIZE;
		areaOfeffect.top = position.y - TILESIZE;
	}
};

class BigDaddy : public Enemy
{
public:
	sf::FloatRect areaOfeffect = sf::FloatRect(0, 0, TILESIZE * 3, TILESIZE * 3);
	BigDaddy()
	{
		actionSpeed = 1;
		id = EnemyID::BigDaddy;
		hp *= 10;
		maxHp = hp;
		damage *= 3;
		speed *= 1;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
	void move(sf::Vector2f position) override
	{
		this->position -= position;
		boundRect.left -= position.x;
		boundRect.top -= position.y;
		areaOfeffect.left -= position.x;
		areaOfeffect.top -= position.y;
	}
	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		boundRect.left = position.x;
		boundRect.top = position.y;
		areaOfeffect.left = position.x - TILESIZE;
		areaOfeffect.top = position.y - TILESIZE;
	}
};

class PsychicEmitter : public Enemy
{
public:
	PsychicEmitter()
	{
		id = EnemyID::PsychicEmitter;
		hp *= 4;
		maxHp = hp;
		damage *= 0;
		speed *= 1;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
};

class ThreeHundredWatts : public Enemy
{
public:
	ThreeHundredWatts()
	{
		id = EnemyID::ThreeHundredWatts;
		hp *= 5;
		maxHp = hp;
		damage *= 1;
		speed *= 0.9;
	}
	void update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size) override;
};
