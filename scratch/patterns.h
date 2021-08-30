#pragma once
#include <SFML\Graphics.hpp>
#include "defValues.h"

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
	//std::shared_ptr<sf::RectangleShape> texture;
	std::shared_ptr<sf::RectangleShape> texture;
	sf::FloatRect boundRect;
public:
	HasACollision() 
	{
		texture = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape);
	}
	sf::RectangleShape& getTexture()
	{
		return *texture;
	}
	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		texture->setPosition(position);
		boundRect.left = position.x;
		boundRect.top = position.y;
	}
	void move(sf::Vector2f position) override
	{
		this->position += position;
		texture->setPosition(this->position);
		boundRect.left += position.x;
		boundRect.top += position.y;
	}
	sf::FloatRect getBoundRect()
	{
		return boundRect;
	}
	void setBoundRect(sf::FloatRect rect)
	{
		boundRect = rect;
		move(sf::Vector2f(0,0));
	}
};

class HasAnAnimation : public HasACollision
{
protected:
	float animationSpeed = 1.0;
	float animationProgress = 0;
	int frame = 0;
	int maxFrame = 4;
	sf::IntRect animationFrame;
public:
	void updateAnimation(float dtAsSeconds)
	{
		animationProgress -= dtAsSeconds;
		if (animationProgress < 0)
		{
			animationProgress = animationSpeed;
			animationFrame = sf::IntRect(0 + frame * 100, 0, 100, 100 );
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
	
};