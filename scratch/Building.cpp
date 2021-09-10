#include "Building.h"
#include <iostream>
#include "defValues.h"

BuildingType Building::getType()
{
	return type;
}

ActionID Turret::update(float dtAsSeconds) 
{
	updateAnimation(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		switch (id)
		{
		case BuildingID::none:
			return ActionID::none;
			break;
		case BuildingID::Turret1:
			return ActionID::ShootProjectile;
			break;
		
		default:break;
		}
	}
	return ActionID::none;
}

ActionID RocketLauncher::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		switch (id)
		{
		case BuildingID::none:
			return ActionID::none;
			break;
		case BuildingID::RocketLauncher1:
			return ActionID::LaunchRocket;
			break;

		default:break;
		}
	}
	return ActionID::none;
}

ActionID HangarBay::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		if (FighterIsNotReleased)
		{
			FighterIsNotReleased = false;
			switch (id)
			{
			case BuildingID::none:
				return ActionID::none;
				break;
			case BuildingID::HangarBay1:
				return ActionID::ReleaseFighter;
				break;
			default:break;
			}
		}
		
	}
	return ActionID::none;
}

ActionID LaserTurret::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		switch (id)
		{

		case BuildingID::LaserTurret1:
			return ActionID::ShootLaser;
			break;

		default:
			break;
		}
	}
	return ActionID::none;
}

ActionID Generator::update(float dtAsSeconds)
{
	updateAnimation(dtAsSeconds);
	if (cooldownIsReady(dtAsSeconds))
	{
		switch (id)
		{

		case BuildingID::EnergyGenerator:
			return ActionID::ProduceEnergy;
			break;

		case BuildingID::MineralsGenerator:
			return ActionID::ProduceMinerals;
			break;

		default:
			break;
		}
	}
	return ActionID::none;
}
