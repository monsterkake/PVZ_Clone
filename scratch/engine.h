#pragma once
#include <SFML/Graphics.hpp>
#include "ResourseContainer.h"
//#include "tile.h"
#include "gameinterface.h"
#include "tileMap.h"
#include "BuildingID.h"
#include "states.h"
#include "projectile.h"
//#include "enemy.h"
#include "buildingType.h"
#include "unitContainer.h"
#include "enemyContainer.h"
#include "researchPopUpWindow.h"
#include "techTree.h"

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
    UnitContainer UnitContainer;
    std::shared_ptr<EnemyContainer> enemyContainer;
    //EnemyContainer enemyContainer;
    
    ResearchPopUpWindow researchWindow;



    //Mouse handling
    sf::Vector2f mousePosition;
    BuildingType SelectedBuildingType = BuildingType::none;
    BuildingID SelectedBuilding = BuildingID::none;
    MouseStates MouseState = MouseStates::NotOccupied;
    sf::Vector2f savedPressLeftClickLocation;

    bool showResearchWindow = false;

    bool isShiftButtonPressed = false;

    bool DebugMode = false;
    bool spawnEnemies = true;

    int resourseEnergy = 10;
    int resourseMinerals = 10;

    int baseEnergyIncome = 1;
    int baseMineralsIncome = 1;
    int baseResearchIncome = 10;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:

    
    // Конструктор движка
    Engine();

    // Функция старт вызовет все приватные функции
    void start();

};