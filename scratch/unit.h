#pragma once
#include "patterns.h"
#include "unitType.h"
#include "unitID.h"

class Fighter : public Unit
{
public:
	
	void update(float dtAsSeconds, sf::Vector2f target) override;
	Fighter()
	{
		type = UnitType::Fighter;
		speed = 250.0;
	}
};