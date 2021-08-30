
#include <SFML\Graphics.hpp>
#include "patterns.h"
#include <string>
#include "defValues.h"
#include "Button.h"
#include "label.h"

class GameInterface : public Moveable
{
public:
	Button destroyButton;
	Button BuildingButtons[AMOUNT_OF_Building_BUTTONS];
	Button economyButtons[AMOUNT_OF_ECONOMY_BUTTONS];
	Label energyLabel;
	Label mineralsLabel;

	GameInterface();
};

