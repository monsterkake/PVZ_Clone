#include "unit.h"

void Fighter::update(float dtAsSeconds, sf::Vector2f target)
{
	sf::Vector2f attackPosition;
	attackPosition.x = target.x - FIGHTER_ATTACK_DISTANCE + rand() % 10 - 5;
	attackPosition.y = target.y + rand() % 10 - 5;

	float dx = speed;
	float dy = speed;

	if (attackPosition.y - position.y < 0)
	{
		dy *= -1;
	}
	if (attackPosition.x - position.x < 0)
	{
		dx *= -1;
	}

	move(sf::Vector2f(dtAsSeconds * dx, dtAsSeconds * dy));

	if (cooldownIsReady(dtAsSeconds))
	{
		ReadyToFire = true;
	}
}