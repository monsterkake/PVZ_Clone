#pragma once
#include <SFML\Graphics.hpp>
#include "patterns.h"
#include "Building.h"
#include "defValues.h"




class Tile : public Moveable
{
public:
	Building Building;
	sf::IntRect rec;
	void placeBuilding();
};


