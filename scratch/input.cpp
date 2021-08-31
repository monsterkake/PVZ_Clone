#include "engine.h"

#include "defValues.h"
#include <iostream>


void Engine::input()
{
	sf::Vector2f mPos;
	while (m_Window.pollEvent(event))
	{

		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;
		case Event::Resized:
			ResourseContainer.resizeTextures(sf::Vector2f(m_Window.getSize()));
			break;
		case sf::Event::MouseButtonPressed:
			//Get mouse position
			mPos = sf::Vector2f(sf::Mouse::getPosition());
			// If left button pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//Check interface buttons
				if (MouseState == MouseStates::NotOccupied)
				{
					// check if Building button is clicked
					for (int i = 0; i < AMOUNT_OF_Building_BUTTONS; i++)
					{
						if (gameInterface.BuildingButtons[i].getTexture().getGlobalBounds().contains(mPos))
						{
							SelectedBuildingType = BuildingType::turret;
							MouseState = MouseStates::build;
							switch (i)
							{
							case 0:
								SelectedBuilding = BuildingID::t0;
								break;
							case 1:
								SelectedBuilding = BuildingID::RocketLauncher1;
								break;
							case 2:
								SelectedBuilding = BuildingID::HangarBay1;
								break;
							case 3:
								SelectedBuilding = BuildingID::t3;
								break;
							case 4:
								SelectedBuilding = BuildingID::t4;
								break;
							case 5:
								SelectedBuilding = BuildingID::t5;
								break;
							case 6:
								SelectedBuilding = BuildingID::t6;
								break;
							case 7:
								SelectedBuilding = BuildingID::t7;
								break;
							default:break;
							}
						}
					}
					// check if ECONOMY button is clicked
					for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
					{
						if (gameInterface.economyButtons[i].getTexture().getGlobalBounds().contains(mPos))
						{
							SelectedBuildingType = BuildingType::economy;
							MouseState = MouseStates::build;
							switch (i)
							{
							case 0:
								SelectedBuilding = BuildingID::energyGenerator;
								break;
							case 1:
								SelectedBuilding = BuildingID::mineralsGenerator;
								break;
								/*case 2:
									SelectedBuilding = BuildingID::t2;
									break;
								case 3:
									SelectedBuilding = BuildingID::t3;
									break;
								case 4:
									SelectedBuilding = BuildingID::t4;
									break;
								case 5:
									SelectedBuilding = BuildingID::t5;
									break;
								case 6:
									SelectedBuilding = BuildingID::t6;
									break;
								case 7:
									SelectedBuilding = BuildingID::t7;
									break;*/
							default:break;
							}
						}
					}
					//Check destroy button
					if (gameInterface.destroyButton.getTexture().getGlobalBounds().contains(mPos))
					{
						MouseState = MouseStates::destroy;
					}
				}
				//Check grass tiles
				//Build mode
				if (MouseState == MouseStates::build)
				{
					for (int i = 0; i < AMOUNT_OF_LINES; i++)
					{
						for (int j = 0; j < TILES_IN_A_LINE; j++)
						{
							if (tileMap.lines[i].tiles[j].rec.contains(sf::Vector2i(mPos)))
							{
								if (resourseEnergy >= int(SelectedBuilding))
								{
									if (SelectedBuilding == BuildingID::HangarBay1)
									{
										ProjectileContainer.addHangar();
									}
									resourseEnergy -= int(SelectedBuilding);
									tileMap.lines[i].tiles[j].Building.id = SelectedBuilding;
									tileMap.lines[i].tiles[j].Building.type = SelectedBuildingType;
								}
								
								if (!isShiftButtonPressed) 
								{
									SelectedBuilding = BuildingID::none;
									MouseState = MouseStates::NotOccupied;
								}
								
							}
						}
					}
				}
				else
					//Destory mode
					if (MouseState == MouseStates::destroy)
					{
						for (int i = 0; i < AMOUNT_OF_LINES; i++)
						{
							for (int j = 0; j < TILES_IN_A_LINE; j++)
							{
								if (tileMap.lines[i].tiles[j].rec.contains(sf::Vector2i(mPos)))
								{
									tileMap.lines[i].tiles[j].Building.id = BuildingID::none;
									tileMap.lines[i].tiles[j].Building.type = BuildingType::none;
								}
							}
						}
					}


			}
			else
				// If right button pressed
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					MouseState = MouseStates::NotOccupied;
					SelectedBuildingType = BuildingType::none;
				}
			break;
			//Check keyboard keys
			// If pressed
		case sf::Event::KeyPressed:
			//std::cout << event.key.code << std::endl;

			if (event.key.code == sf::Keyboard::Escape)
			{
				m_Window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::Tilde)
			{
				DebugMode = !DebugMode;
				break;
			}
			if (event.key.code == sf::Keyboard::LShift)
			{
				isShiftButtonPressed = true;
				break;
			}
			break;
			//If released
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::LShift)
			{
				isShiftButtonPressed = false;
				break;
			}
		default: break;
		}
	}

}