#include "enemy.h"
#include <math.h>

void Scout::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (canMove)
	{
		move(sf::Vector2f(dtAsSeconds * speed, 0));
	}
}

void Swarmling::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (canMove)
	{
		move(sf::Vector2f(dtAsSeconds * speed, 0));
	}
}

void Avoider::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (canMove)
	{
		move(sf::Vector2f(dtAsSeconds * speed, 0));
	}
	//change line
	if (0 <= (line + newLine) && (line + newLine) < AMOUNT_OF_LINES) 
	{
		if (hp <= (maxHp / 2))
		{
			if (!hasChangedLine)
			{
				if (initialPositionY + TILESIZE >= position.y && initialPositionY - TILESIZE <= position.y)
				{
					move(sf::Vector2f(0, dtAsSeconds * speed * 4 * newLine));
				}
				else
				{
					hasChangedLine = true;
				}
			}
		}
	}
}

void Lardster::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (canMove)
	{
		move(sf::Vector2f(dtAsSeconds * speed, 0));
	}
}

void Animuta::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (canMove)
	{
		move(sf::Vector2f(dtAsSeconds * speed, 0));
	}
}
