#include "Building.h"
#include <iostream>
#include "defValues.h"

Building::Building()
{
	
	//texture->setOutlineColor(sf::Color::Black);
	//texture->setFillColor(sf::Color::Red);
	//texture->setOutlineThickness(1);
	//texture->setSize(sf::Vector2f(TILESIZE / 2, TILESIZE / 2));
	//texture->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

ProjectileID Building::update(float dtAsSeconds)
{
	cooldown = cooldown - dtAsSeconds;
	if (cooldown < 0) 
	{
		cooldown = actionSpeed;
		switch (id) 
		{
		case BuildingID::none:
			return ProjectileID::none;
			break;
		case BuildingID::t0:
			return ProjectileID::p0;
			break;
		case BuildingID::RocketLauncher1:
			return ProjectileID::Rocket1;
			break;
		case BuildingID::HangarBay1:
			return ProjectileID::Fighter1;
			break;
		case BuildingID::t3:
			return ProjectileID::p3;
			break;
		case BuildingID::t4:
			return ProjectileID::p4;
			break;
		case BuildingID::t5:
			return ProjectileID::p5;
			break;
		case BuildingID::t6:
			return ProjectileID::p6;
			break;
		case BuildingID::t7:
			return ProjectileID::p7;
			break;
		default:break;
		}
	}
	return ProjectileID::none;
}

ActionID Building::act(float dtAsSeconds)
{
	cooldown = cooldown - dtAsSeconds;
	if (cooldown < 0)
	{
		cooldown = actionSpeed;
		switch (id)
		{

		case BuildingID::energyGenerator:
			return ActionID::a0;
			break;

		case BuildingID::mineralsGenerator:
			return ActionID::a1;
			break;

		default:
			break;
		}
	}
	return ActionID::none;
}

BuildingType Building::getType()
{
	return type;
}
