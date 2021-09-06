#pragma once

#include <SFML\Graphics.hpp>
#include "patterns.h"
#include "defValues.h"
#include "label.h"
#include "widget.h"

class Button :  public Widget
{
	std::shared_ptr<Label> label;
public:
	
	Button()
	{
		label = std::shared_ptr<Label>(new Label);
		setBoundRect(sf::FloatRect(0, 0, BUTTON_SIZE, BUTTON_SIZE));
	};
	void setText(std::string string)
	{
		label->setText(string);
	}
	sf::Text& getText()
	{
		return label->getText();
	}
	void setPosition(sf::Vector2f position) override
	{
		this->position = position + offset;
		boundRect.left = this->position.x;
		boundRect.top = this->position.y;
		label->setPosition(this->position + sf::Vector2f(0,50));
	}
	void move(sf::Vector2f position) override
	{
		this->position += position + offset;
		boundRect.left += this->position.x;
		boundRect.top += this->position.y;
		label->setPosition(this->position + sf::Vector2f(0, 50));
	}
};