#include "gameinterface.h"
#include "defValues.h"

#define DISTANCE_BETWEEN_BUTTONS 70


GameInterface::GameInterface()
{
	setPosition(sf::Vector2f(20, 20));

	destroyButton.setString("destroy");
	destroyButton.setPosition(sf::Vector2f((position.x + 2 * DISTANCE_BETWEEN_BUTTONS + AMOUNT_OF_Building_BUTTONS * DISTANCE_BETWEEN_BUTTONS), position.y));

	for (int i = 0; i < AMOUNT_OF_Building_BUTTONS; i++)
	{
		std::string temp;
		temp = "Button ";
		temp.push_back(char(i + 48));
		BuildingButtons[i].setString(temp);
		BuildingButtons[i].setPosition(sf::Vector2f((position.x + i * DISTANCE_BETWEEN_BUTTONS), position.y));
	}
	for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
	{
		std::string temp;
		temp = "Button ";
		temp.push_back(char(i + 48));
		economyButtons[i].setString(temp);
		economyButtons[i].setPosition(sf::Vector2f((position.x + i * DISTANCE_BETWEEN_BUTTONS), position.y + DISTANCE_BETWEEN_BUTTONS));
	}
	//Resourse labels
	energyLabel.setString("Energy ");
	energyLabel.setPosition(sf::Vector2f(destroyButton.getPosition().x + DISTANCE_BETWEEN_BUTTONS, destroyButton.getPosition().y));
	mineralsLabel.setString("Minerals ");
	mineralsLabel.setPosition(sf::Vector2f(destroyButton.getPosition().x +  DISTANCE_BETWEEN_BUTTONS, destroyButton.getPosition().y + DISTANCE_BETWEEN_BUTTONS / 2) );
}
