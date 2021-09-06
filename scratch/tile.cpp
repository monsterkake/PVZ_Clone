#include "tile.h"
#include "defValues.h"

Tile::Tile()
{
	building = nullptr;
}

void Tile::placeBuilding(BuildingID id)
{
	if (id == BuildingID::Turret1)
	{
		switch (id)
		{
		case BuildingID::Turret1:
			building = std::shared_ptr<Building>(new Turret);
			building->id = id;
			building->type = BuildingType::Turret;
			break;
		default:break;
		}
	}

	if (id == BuildingID::RocketLauncher1)
	{
		switch (id)
		{
		case BuildingID::RocketLauncher1:
			building = std::shared_ptr<Building>(new RocketLauncher);
			building->id = id;
			building->type = BuildingType::RocketLauncher;
			break;
		default:break;
		}
	}

	if (id == BuildingID::HangarBay1)
	{
		switch (id)
		{
		case BuildingID::HangarBay1:
			building = std::shared_ptr<Building>(new HangarBay);
			building->id = id;
			building->type = BuildingType::HangarBay;
			break;
		default:break;
		}
	}
	if (id == BuildingID::LaserTurret1)
	{
		switch (id)
		{
		case BuildingID::LaserTurret1:
			building = std::shared_ptr<Building>(new LaserTurret);
			building->id = id;
			building->type = BuildingType::LaserTurret;
			break;
		default:break;
		}
	}

	if (id == BuildingID::EnergyGenerator || id == BuildingID::MineralsGenerator)
	{
		
		building = std::shared_ptr<Building>(new Generator);
		building->id = id;
		building->type = BuildingType::Generator;
		
	}
	if (building != nullptr) 
	{
		building->setPosition(sf::Vector2f(position.x, position.y));
	}
}

void Tile::removeBuilding()
{
	building = nullptr;
}
