#include "tileMap.h"
#include "defValues.h"

TileMap::TileMap()
{
	this->setPosition(sf::Vector2f(TILEMAP_POSITION_X, TILEMAP_POSITION_Y));

	for (int i = 0; i < AMOUNT_OF_LINES; i++)
	{
		for (int j = 0; j < TILES_IN_A_LINE; j++)
		{
			lines[i].tiles[j].setPosition(sf::Vector2f(j * TILESIZE, i * TILESIZE) + position);
			//lines[i].tiles[j].placeBuilding();
			lines[i].tiles[j].rec = sf::IntRect(lines[i].tiles[j].getPosition().x, lines[i].tiles[j].getPosition().y, TILESIZE,TILESIZE);
		}
	}
}
