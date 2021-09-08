#pragma once
#include "patterns.h"
#include <SFML\Graphics.hpp>
#include "widget.h"

class Label : public Widget
{
protected:
	std::string stringBase;
	std::shared_ptr<sf::Text> text;
	sf::Font font;
public:
	
	
	Label() 
	{
		font.loadFromFile("resourses/fonts/arial.ttf");
		text = std::shared_ptr<sf::Text>(new sf::Text);
		stringBase = "";
		text->setString(stringBase);
		text->setFont(font);
		text->setFillColor(sf::Color::White);
		text->setOutlineColor(sf::Color::Black);
		text->setCharacterSize(13);
	}
	
	void setPosition(sf::Vector2f position) override
	{
		this->position = position + offset;
		text->setPosition(this->position);
	}
	void setStringBase(std::string string)
	{
		this->stringBase = string;
		text->setString(stringBase);
	}
	std::string getStringBase()
	{
		return stringBase;
	}
	void setText(std::string string)
	{
		//this->string = string;
		text->setString(stringBase + " " + string);
	}
	sf::Text& getText() 
	{
		return *text;
	}
};