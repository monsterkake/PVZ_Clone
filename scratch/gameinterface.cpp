#include "gameinterface.h"
#include "defValues.h"

#define DISTANCE_BETWEEN_BUTTONS 70


GameInterface::GameInterface()
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
	//energyLabel.setString("Energy ");
	energyLabel.setStringBase("Energy ");
	energyLabel.setPosition(sf::Vector2f(researchButton.getPosition().x + DISTANCE_BETWEEN_BUTTONS, researchButton.getPosition().y));

	
	mineralsLabel.setStringBase("Minerals ");
	mineralsLabel.setPosition(sf::Vector2f(researchButton.getPosition().x +  DISTANCE_BETWEEN_BUTTONS, researchButton.getPosition().y + DISTANCE_BETWEEN_BUTTONS / 2) );
}
