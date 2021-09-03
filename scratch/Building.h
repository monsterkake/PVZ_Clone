#pragma once
#include "patterns.h"
#include <SFML\Graphics.hpp>
#include <memory.h>
#include "BuildingID.h"
//#include "projectileID.h"
#include "actionID.h"
#include "buildingType.h"

class Building : public HasACollision, public HasACooldown
{
public:
    BuildingType type = BuildingType::none;
    Building();
    BuildingID id = BuildingID::none;
    virtual ActionID update(float dtAsSeconds) = 0;
    BuildingType getType();
};

class Turret : public Building
{
public:
    Turret()
    {
        actionSpeed = 1.0;
    }
    ActionID update(float dtAsSeconds) override;
};

class RocketLauncher : public Building
{
public:
    RocketLauncher()
    {
        actionSpeed = 1.0;
    }
    ActionID update(float dtAsSeconds) override;
};

class HangarBay : public Building
{
public:
    HangarBay()
    {
        actionSpeed = 1.0;
    }
    bool FighterIsNotReleased = true;
    ActionID update(float dtAsSeconds) override;
};

class LaserTurret : public Building
{
public:
    LaserTurret() 
    {
        actionSpeed = 2.0;
    }
    ActionID update(float dtAsSeconds) override;
};

class Generator : public Building
{
public:
    Generator()
    {
        actionSpeed = 1.0;
    }
    ActionID update(float dtAsSeconds) override;
};