#pragma once
#include <SFML\Graphics.hpp>
#include "defValues.h"
#include "unitType.h"
#include "unitID.h"
#include <iostream>


class Moveable 
{
protected:
	sf::Vector2f position;
public:
	virtual void setPosition(sf::Vector2f position)
	{
		this->position = position;
	}
	sf::Vector2f getPosition() 
	{
		return position;
	}
	virtual void move(sf::Vector2f position)
	{
		this->position += position;
	}
};

class HasACollision : public Moveable 
{
protected:
	sf::FloatRect boundRect;
public:
	HasACollision() 
	{
		
	}

	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		boundRect.left = position.x;
		boundRect.top = position.y;
	}
	void move(sf::Vector2f position) override
	{
		this->position += position;
		boundRect.left += position.x;
		boundRect.top += position.y;
	}
	virtual sf::FloatRect getBoundRect()
	{
		return boundRect;
	}
	void setBoundRect(sf::FloatRect rect)
	{
		boundRect = rect;
		move(sf::Vector2f(0,0));
	}
	bool isClicked(sf::Vector2f mpos) 
	{
		if (boundRect.contains(mpos))
		{
			return true;
		}
		else 
		{
			return false;
		}
		
	};
};

class HasAnAnimation : public HasACollision
{
protected:
	float animationSpeed = 1.0;
	float animationProgress = 0;
	int frame = 0;
	int maxFrame = 4;
	sf::IntRect animationFrame;
	int frameSize = SPRITE_SIZE;
	
public:
	void updateAnimation(float dtAsSeconds)
	{
		animationProgress -= dtAsSeconds;
		if (animationProgress < 0)
		{
			animationProgress = animationSpeed;
			animationFrame = sf::IntRect(0 + frame * frameSize, 0, frameSize, frameSize);
			//animationFrame.left += 100
			frame++;
			if (frame > maxFrame)
				frame = 0;
		}
	}
	sf::IntRect getFrame() 
	{
		return animationFrame;
	}
	void setFrameSize(int size)
	{
		frameSize = size;
	}

};

class HasACooldown 
{
protected:
	float actionSpeed = 1.0;
	float cooldown = actionSpeed;

	bool cooldownIsReady(float dtAsSeconds)
	{
		cooldown = cooldown - dtAsSeconds;
		if (cooldown < 0)
		{
			cooldown = actionSpeed;
			return true;
		}
		else
		{
			return false;
		}
	};
};

class HasHitPoints 
{
protected:
	float hp;
	float maxHp = 0;
public:

	void recieveDamage(float damage)
	{
		hp -= damage;
	}
	void setHp(float hp)
	{
		this->hp = hp;
	}
	float getHp()
	{
		return hp;
	}
};

class Unit : public HasAnAnimation, public HasACooldown, public HasHitPoints
{
protected:
	
	float speed;
	
	bool ReadyToFire = false;
public:
	UnitID id;
	UnitType type;
	sf::Vector2i parentIndex;

	virtual void update(float dtAsSeconds, sf::Vector2f target) = 0;

	bool isReadyToFire()
	{
		if (ReadyToFire)
		{
			ReadyToFire = false;
			return true;
		}
		return false;
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

class HasARenderTexture 
{
protected:
	sf::RenderTexture m_renderTexture;
	std::shared_ptr<sf::Sprite> m_sprite;
public:
	HasARenderTexture() 
	{
		sf::Vector2f resolution;
		resolution.x = sf::VideoMode::getDesktopMode().width;
		resolution.y = sf::VideoMode::getDesktopMode().height;
		m_sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite);
		m_renderTexture.create(resolution.x, resolution.y);
	}
	sf::Sprite& getSprite()
	{
		return *m_sprite;
	};
};

class HasRotation
{
protected:
	float angle = 0;
public:
	void setAngle(float angle)
	{
		this->angle = angle ;
	}
	float getAngle()
	{
		return angle;
	}
};

class Item
{
public:
	Item();
};

class Container
{
public:
	Container();
	std::shared_ptr<Item> items;
};

