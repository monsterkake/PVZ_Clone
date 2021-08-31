#pragma once
//#include "tile.h"
#include "tileLine.h"
#include <SFML\Graphics.hpp>

class TileMap : public Moveable
{

public:
	tileLine lines[AMOUNT_OF_LINES];
	TileMap();
	
};

