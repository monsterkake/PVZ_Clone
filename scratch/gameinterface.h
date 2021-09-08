
#include <SFML\Graphics.hpp>
#include "patterns.h"
#include <string>
#include "defValues.h"
#include "Button.h"
#include "label.h"

#define DISTANCE_BETWEEN_BUTTONS 70

class GameInterface : public Moveable, public HasARenderTexture
{
private:
	sf::Texture TextureButtonBase;
	sf::Sprite buttonBaseSprite;
	sf::Color hoveredColor = sf::Color(250, 250, 250, 255);
	sf::Color notHoveredColor = sf::Color(250, 100, 100, 255);
public:
	//base
	Button destroyButton;
	Button BuildingButtons[AMOUNT_OF_BUILDING_BUTTONS];
	Button economyButtons[AMOUNT_OF_ECONOMY_BUTTONS];
	Button researchButton;
	Label energyLabel;
	Label mineralsLabel;
	//Research

	GameInterface() 
	{
		setPosition(sf::Vector2f(20, 20));
		//destroyButton
		destroyButton.setText("destroy");
		destroyButton.setPosition(sf::Vector2f((position.x + 2 * DISTANCE_BETWEEN_BUTTONS + AMOUNT_OF_BUILDING_BUTTONS * DISTANCE_BETWEEN_BUTTONS), position.y));
		//Buttons for turrets
		for (int i = 0; i < AMOUNT_OF_BUILDING_BUTTONS; i++)
		{
			std::string temp;
			temp = "Button ";
			temp.push_back(char(i + 48));
			BuildingButtons[i].setText(temp);
			BuildingButtons[i].setPosition(sf::Vector2f((position.x + i * DISTANCE_BETWEEN_BUTTONS), position.y));
		}
		//Buttons for economy buildings
		for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
		{
			std::string temp;
			temp = "Button ";
			temp.push_back(char(i + 48));
			economyButtons[i].setText(temp);
			economyButtons[i].setPosition(sf::Vector2f((position.x + i * DISTANCE_BETWEEN_BUTTONS), position.y + DISTANCE_BETWEEN_BUTTONS));
		}
		//Button for reaaserch 
		researchButton.setText("Research");
		researchButton.setPosition(sf::Vector2f((position.x + 3 * DISTANCE_BETWEEN_BUTTONS + AMOUNT_OF_BUILDING_BUTTONS * DISTANCE_BETWEEN_BUTTONS), position.y));
		//Resourse labels
		energyLabel.setStringBase("Energy ");
		energyLabel.setPosition(sf::Vector2f(researchButton.getPosition().x + DISTANCE_BETWEEN_BUTTONS, researchButton.getPosition().y));


		mineralsLabel.setStringBase("Minerals ");
		mineralsLabel.setPosition(sf::Vector2f(researchButton.getPosition().x + DISTANCE_BETWEEN_BUTTONS, researchButton.getPosition().y + DISTANCE_BETWEEN_BUTTONS / 2));

		TextureButtonBase.loadFromFile("resourses/sprites/buttonBase.png");
		buttonBaseSprite.setTexture(TextureButtonBase);
		buttonBaseSprite.setScale(0.5, 0.5);
	}

	void updateSprite(sf::Vector2f mpos,float resourseEnergy,float resourseMinerals)
	{
		m_renderTexture.clear(sf::Color(0, 0, 0, 0));
		
		//Draw Interface
		//Draw Building Buttons
		
		for (int i = 0; i < AMOUNT_OF_BUILDING_BUTTONS; i++)
		{
			if (BuildingButtons[i].isHovered(mpos)) 
			{
				buttonBaseSprite.setColor(hoveredColor);
			}
			else 
			{
				buttonBaseSprite.setColor(notHoveredColor);
			}
			buttonBaseSprite.setPosition(BuildingButtons[i].getPosition());
			m_renderTexture.draw(buttonBaseSprite);
			m_renderTexture.draw(BuildingButtons[i].getText());
		}
		//Draw economy Buttons
		for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
		{
			if (economyButtons[i].isHovered(mpos))
			{
				buttonBaseSprite.setColor(hoveredColor);
			}
			else
			{
				buttonBaseSprite.setColor(notHoveredColor);
			}
			buttonBaseSprite.setPosition(economyButtons[i].getPosition());
			m_renderTexture.draw(buttonBaseSprite);
			m_renderTexture.draw(economyButtons[i].getText());
		}

		//Draw destroy button
		if (destroyButton.isHovered(mpos))
		{
			buttonBaseSprite.setColor(hoveredColor);
		}
		else
		{
			buttonBaseSprite.setColor(notHoveredColor);
		}
		buttonBaseSprite.setPosition(destroyButton.getPosition());
		m_renderTexture.draw(buttonBaseSprite);
		m_renderTexture.draw(destroyButton.getText());

		//Draw research button
		if (researchButton.isHovered(mpos))
		{
			buttonBaseSprite.setColor(hoveredColor);
		}
		else
		{
			buttonBaseSprite.setColor(notHoveredColor);
		}
		buttonBaseSprite.setPosition(researchButton.getPosition());
		m_renderTexture.draw(buttonBaseSprite);
		m_renderTexture.draw(researchButton.getText());

		//return sprite scale to normal

		//Draw labels
		energyLabel.setText(std::string(": " + std::to_string(resourseEnergy)));
		m_renderTexture.draw(energyLabel.getText());
		mineralsLabel.setText(std::string(": " + std::to_string(resourseMinerals)));
		m_renderTexture.draw(mineralsLabel.getText());

		//test

		//update Sprite
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
	}
};

