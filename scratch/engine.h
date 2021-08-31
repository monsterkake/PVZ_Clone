#pragma once
#include <SFML/Graphics.hpp>
#include "ResourseContainer.h"
#include "tile.h"
#include "gameinterface.h"
#include "tileMap.h"
#include "BuildingID.h"
#include "states.h"
#include "projectile.h"
#include "enemy.h"
#include "buildingType.h"

using namespace sf;




class Engine
{
private:
    Event event;
    RenderWindow m_Window;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    ResourseContainer ResourseContainer;
    GameInterface gameInterface;
    TileMap tileMap;
    ProjectileContainer ProjectileContainer;
    EnemyContainer EnemyContainer;

    BuildingType SelectedBuildingType = BuildingType::none;
    BuildingID SelectedBuilding = BuildingID::none;
    MouseStates MouseState = MouseStates::NotOccupied;

    bool isShiftButtonPressed = false;

    bool DebugMode = false;

    int resourseEnergy = 10;
    int resourseMinerals = 10;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:

    
    // Конструктор движка
    Engine();

    // Функция старт вызовет все приватные функции
    void start();

};