#pragma once
#include "popUpWindow.h"
#include "techTree.h"
#include "label.h"

class ResearchPopUpWindow : public PopUpWindow
{
	sf::Texture buttonBase;
	sf::Texture closeButtonBase;
	sf::Sprite buttonBaseSprite;
	sf::Sprite closeButtonBaseSprite;

public:
	TechnologyID selectedResearch = TechnologyID::none;
	TechnologyTree techTree;

	Button closeButton;

	Button technologyButtons[TECHNOLOGY_TREE_LENGTH];

	Label progressBar;

	ResearchPopUpWindow()
	{
		//Textures to sprites
		closeButtonBase.loadFromFile("resourses/sprites/closeButtonBase.png");
		closeButtonBaseSprite.setTexture(closeButtonBase);
		closeButtonBaseSprite.setScale(0.2, 0.2);

		buttonBase.loadFromFile("resourses/sprites/buttonBase.png");
		buttonBaseSprite.setTexture(buttonBase);
		buttonBaseSprite.setScale(1, 0.5);

		//what am i doing with my life?
		m_isGrabbed = std::shared_ptr<bool>(new bool);
		*m_isGrabbed = false;
		//collision configure

		size = sf::Vector2f(1000, 500);
		boundRect.height = size.y;
		boundRect.width = size.x;
		popUpWindowBase.loadFromFile("resourses/sprites/PopUpWindowBase.png");
		popUpWindowBaseSprite.setTexture(popUpWindowBase);
		popUpWindowBaseSprite.setScale(size.x / SPRITE_SIZE, size.y / SPRITE_SIZE);
		name.setText("ResearchWindow");
		name.setPosition(sf::Vector2f(0, 0));
		name.setOffset();
		// draw base and text
		m_renderTexture.draw(popUpWindowBaseSprite);
		m_renderTexture.draw(name.getText());


		//position configure
		setPosition(sf::Vector2f(0, 0));
		updateOriginalPosition();
		//configure widgets
		closeButton.setBoundRect(sf::FloatRect(0, 0, SPRITE_SIZE / 5, SPRITE_SIZE / 5));
		closeButton.setPosition(sf::Vector2f(this->getPosition().x + size.x - SPRITE_SIZE / 5, this->getPosition().y));
		closeButton.setOffset();

		for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
		{
			technologyButtons[i].setBoundRect(sf::FloatRect(0,0,100,50));
		}

		technologyButtons[int(TechnologyID::Sticks)].setText("Sticks");
		technologyButtons[int(TechnologyID::Stones)].setText("Stones");
		technologyButtons[int(TechnologyID::SticksAndStones)].setText("SticksAndStones");

		technologyButtons[int(TechnologyID::Sticks)].setPosition(sf::Vector2f(100,100));
		technologyButtons[int(TechnologyID::Stones)].setPosition(sf::Vector2f(100, 200));
		technologyButtons[int(TechnologyID::SticksAndStones)].setPosition(sf::Vector2f(300, 150));

		technologyButtons[int(TechnologyID::Sticks)].setOffset();
		technologyButtons[int(TechnologyID::Stones)].setOffset();
		technologyButtons[int(TechnologyID::SticksAndStones)].setOffset();

		progressBar.setPosition(sf::Vector2f(50, 440));
		progressBar.setStringBase("progress");
		progressBar.setOffset();

		//Draw widgets
		//Draw close Button
		
		closeButtonBaseSprite.setPosition(closeButton.getPosition());
		m_renderTexture.draw(closeButtonBaseSprite);
		//draw technology buttons
		for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
		{
			buttonBaseSprite.setPosition(technologyButtons[i].getPosition());
			technologyButtons[i].getText().setPosition(technologyButtons[i].getPosition() - this->getPosition());
			m_renderTexture.draw(buttonBaseSprite);
			m_renderTexture.draw(technologyButtons[i].getText());
		}

		//draw progress bar
		m_renderTexture.draw(progressBar.getText());
		//test

		//update Sprite
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
	}

	void updateSprite() 
	{
		m_renderTexture.clear(sf::Color(0,0,0,0));
		//m_sprite->setPosition(0,0);
		m_renderTexture.draw(popUpWindowBaseSprite);
		m_renderTexture.draw(name.getText());
		closeButtonBaseSprite.setPosition(closeButton.getPosition() - this->getPosition());
		m_renderTexture.draw(closeButtonBaseSprite);
		//draw technology buttons
		sf::Color savedColor = buttonBaseSprite.getColor();
		for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
		{
			
			if (int(selectedResearch) == i) 
			{
				buttonBaseSprite.setColor(sf::Color(0, 255, 255,255));
			}
			else
			{
				buttonBaseSprite.setColor(savedColor);
				
			}
			buttonBaseSprite.setPosition(technologyButtons[i].getPosition() - this->getPosition());
			m_renderTexture.draw(buttonBaseSprite);
			technologyButtons[i].getText().setPosition(technologyButtons[i].getPosition() - this->getPosition());
			m_renderTexture.draw(technologyButtons[i].getText());
			
		}
		buttonBaseSprite.setColor(savedColor);
		//draw progress bar
		
		progressBar.setText(std::to_string(techTree.technologies[int(selectedResearch)].progress));
		m_renderTexture.draw(progressBar.getText());
		//test

		//update Sprite
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
		//m_sprite->setPosition(this->getPosition());
	}

	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		m_sprite->setPosition(this->position);
		boundRect.left = position.x;
		boundRect.top = position.y;
		closeButton.setPosition(this->getPosition());
		technologyButtons[int(TechnologyID::Sticks)].setPosition(this->getPosition() );
		technologyButtons[int(TechnologyID::Stones)].setPosition(this->getPosition() );
		technologyButtons[int(TechnologyID::SticksAndStones)].setPosition(this->getPosition() );
	}
	void move(sf::Vector2f position) override
	{
		this->position += position;
		m_sprite->setPosition(this->position);
		boundRect.left += position.x;
		boundRect.top += position.y;
		closeButton.setPosition(sf::Vector2f(this->getPosition().x + size.x - SPRITE_SIZE / 5, this->getPosition().y));
		technologyButtons[int(TechnologyID::Sticks)].setPosition(this->getPosition() + sf::Vector2f(100, 100));
		technologyButtons[int(TechnologyID::Stones)].setPosition(this->getPosition() + sf::Vector2f(100, 200));
		technologyButtons[int(TechnologyID::SticksAndStones)].setPosition(this->getPosition() + sf::Vector2f(300, 150));
	}

	void setResearch(TechnologyID research)
	{
		selectedResearch = research;
	}
};