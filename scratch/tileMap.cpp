#include "tileMap.h"
#include "defValues.h"

TileMap::TileMap()
{
	this->setPosition(sf::Vector2f(TILEMAP_POSITION_X, TILEMAP_POSITION_Y));

	for (int i = 0; i < TILES_X; i++)
	{
		for (int j = 0; j < TILES_Y; j++)
		{
			tiles[i][j].setPosition(sf::Vector2f(i * TILESIZE, j * TILESIZE) + position);
			tiles[i][j].placeBuilding();
			tiles[i][j].rec = sf::IntRect(tiles[i][j].getPosition().x, tiles[i][j].getPosition().y, TILESIZE,TILESIZE);
		}
	}
}
