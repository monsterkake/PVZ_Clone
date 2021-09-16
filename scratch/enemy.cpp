#include "enemy.h"
#include <math.h>

void Scout::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);
}

void Swarmling::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);
}

void Avoider::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);
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

void Lardster::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);
}

void Animuta::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);

	if (cooldownIsReady(dtAsSeconds)) 
	{
		for (int i = 0; i < size; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->id != EnemyID::Animuta)
				{
					if (enemy[i]->getBoundRect().intersects(areaOfeffect))
					{
						if (enemy[i]->getSpeed() < this->getSpeed())
						{
							enemy[i]->setSpeed(this->getSpeed()*1.2);
						}
					}
				}
			}
		}
	}
}

void BigDaddy::update(float dtAsSeconds, std::shared_ptr<Enemy>* enemy, int& size)
{
	onUpdate(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		if (hp < maxHp) 
		{
			for (int i = 0; i < size; i++)
			{
				if (enemy[i] != nullptr)
				{
					if (enemy[i]->id != EnemyID::BigDaddy)
					{
						if (enemy[i]->getBoundRect().intersects(areaOfeffect))
						{
							float healing = maxHp - hp;
							if (enemy[i]->getHp() < healing)
								healing = enemy[i]->getHp();
							enemy[i]->recieveDamage(healing);
							hp += healing;
							return;
						}
					}
				}
			}
		}
	}
}
