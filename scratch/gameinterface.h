
#include <SFML\Graphics.hpp>
#include "patterns.h"
#include <string>
#include "defValues.h"
#include "Button.h"
#include "label.h"

class GameInterface : public Moveable
{
public:
	//base
	Button destroyButton;
	Button BuildingButtons[AMOUNT_OF_BUILDING_BUTTONS];
	Button economyButtons[AMOUNT_OF_ECONOMY_BUTTONS];
	Button researchButton;
	Label energyLabel;
	Label mineralsLabel;
	//Research

	GameInterface();
};

