#pragma once
#include "patterns.h"
#include <SFML\Graphics.hpp>
#include "label.h"
#include "defValues.h"
#include "Button.h"
#include "TechnologyID.h"
#include "widget.h"

class PopUpWindow : public HasACollision, public HasARenderTexture
{
protected:
	sf::Vector2f size;
	Label name;
	sf::Texture popUpWindowBase;
	sf::Sprite popUpWindowBaseSprite;
	std::shared_ptr<bool> m_isGrabbed;
	sf::Vector2f originalPosition;
	std::vector<std::shared_ptr<Widget>> Widgets;
public:
	PopUpWindow() 
	{
		//what am i doing with my life?
		m_isGrabbed = std::shared_ptr<bool>(new bool);
		*m_isGrabbed = false;
		//collision configure
		setSize(sf::Vector2f(TECH_POPUPWINDOW_SIZE_X, TECH_POPUPWINDOW_SIZE_Y));
		//boundRect.height = size.y;
		//boundRect.width = size.x;
		//render texture configure
		popUpWindowBase.loadFromFile("resourses/sprites/PopUpWindowBase.png");
		popUpWindowBaseSprite.setTexture(popUpWindowBase);
		popUpWindowBaseSprite.setScale(size.x / SPRITE_SIZE, size.y / SPRITE_SIZE);
		name.setText("PopUpWindow");
		m_renderTexture.draw(popUpWindowBaseSprite);
		m_renderTexture.draw(name.getText());
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
		//position configure
		setPosition(sf::Vector2f(0,0));
		updateOriginalPosition();
	}
	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		m_sprite->setPosition(this->position);
		boundRect.left = position.x;
		boundRect.top = position.y;
	}
	void move(sf::Vector2f position) override
	{
		this->position += position;
		m_sprite->setPosition(this->position);
		boundRect.left += position.x;
		boundRect.top += position.y;
	}
	void setSize(sf::Vector2f size)
	{
		this->size = size;

		boundRect.height = this->size.y;
		boundRect.width = this->size.x;
	}
	sf::Vector2f getSize() 
	{
		return size;
	}
	bool& isGrabbed() 
	{
		return *m_isGrabbed;
	}
	void updateOriginalPosition() 
	{
		originalPosition = position;
	}
	sf::Vector2f getOriginalPosition() 
	{
		return originalPosition;
	}

	void addWidget(std::shared_ptr<Widget> newWidget)
	{
		Widgets.push_back(newWidget);
	}
};
