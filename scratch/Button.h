#pragma once

#include <SFML\Graphics.hpp>
#include "patterns.h"

class Button : public HasACollision
{
	std::string string;
public:
	Button()
	{
		texture = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape);

		texture->setFillColor(sf::Color::Cyan);
		texture->setSize(sf::Vector2f(50, 50));

	};
	void setString(std::string string)
	{
		this->string = string;
	}
	std::string getString()
	{
		return string;
	}
};