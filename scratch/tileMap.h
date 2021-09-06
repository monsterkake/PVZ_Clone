#pragma once

#include "tileLine.h"
#include <SFML\Graphics.hpp>
#include "patterns.h"

class TileMap : public Moveable, public HasARenderTexture
{
protected:
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

public:
	tileLine lines[AMOUNT_OF_LINES];
	TileMap() 
	{

		tileTexture.loadFromFile("resourses/sprites/tileTexture.png");
		tileSprite.setTexture(tileTexture);
		tileSprite.setScale((float)TILESIZE / (float)tileTexture.getSize().x, (float)TILESIZE / (float)tileTexture.getSize().y);
		tileSprite.setColor(sf::Color(100, 100, 0, 100));

		this->setPosition(sf::Vector2f(TILEMAP_POSITION_X, TILEMAP_POSITION_Y));

		for (int i = 0; i < AMOUNT_OF_LINES; i++)
		{
			for (int j = 0; j < TILES_IN_A_LINE; j++)
			{
				tileSprite.setPosition(sf::Vector2f(j * TILESIZE, i * TILESIZE) + position);
				m_renderTexture.draw(tileSprite);
				lines[i].tiles[j].setPosition(sf::Vector2f(j * TILESIZE, i * TILESIZE) + position);
				lines[i].tiles[j].rec = sf::IntRect(lines[i].tiles[j].getPosition().x, lines[i].tiles[j].getPosition().y, TILESIZE, TILESIZE);
			}
		}
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
	};
};

