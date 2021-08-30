#include "tile.h"
#include "defValues.h"

void Tile::placeBuilding()
{
	Building.setPosition(sf::Vector2f(position.x, position.y));

}
