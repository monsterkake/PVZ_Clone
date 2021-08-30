#pragma once
#include "tile.h"
#include <SFML\Graphics.hpp>

class TileMap : public Moveable
{

public:
	Tile tiles[TILES_X][TILES_Y];
	TileMap();
	
};
