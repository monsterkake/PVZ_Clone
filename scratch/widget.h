#pragma once
#include <SFML\Graphics.hpp>

class Widget : public HasACollision
{
protected:
	sf::Vector2f offset;
public:
	Widget() 
	{
		offset = sf::Vector2f(0, 0);
	}
	void setOffset()
	{
		this->offset = position;
	}
	sf::Vector2f getOffset() 
	{
		return offset;
	}
};