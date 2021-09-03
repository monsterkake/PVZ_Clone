#pragma once
#include <SFML\Graphics.hpp>
#include "patterns.h"
#include "Building.h"
#include "defValues.h"
#include "BuildingID.h"



class Tile : public Moveable
{
public:
	std::shared_ptr<Building> building;
	//Building Building;
	sf::IntRect rec;
	Tile();
	void placeBuilding(BuildingID id);
	void removeBuilding();
};


