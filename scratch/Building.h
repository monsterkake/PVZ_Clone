#pragma once
#include "patterns.h"
#include <SFML\Graphics.hpp>
#include <memory.h>
#include "BuildingID.h"
#include "projectileID.h"
#include "actionID.h"
#include "buildingType.h"

class Building : public HasACollision
{
     
public:
    BuildingType type = BuildingType::none;
    Building();
    BuildingID id = BuildingID::none;
    float actionSpeed = 1.0;
    float cooldown = actionSpeed;
    ProjectileID update(float dtAsSeconds);
    ActionID act(float dtAsSeconds);
    BuildingType getType();
    
};

