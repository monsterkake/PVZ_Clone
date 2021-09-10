#include "engine.h"
#include "TechnologyID.h"
#include "defValues.h"
#include <iostream>


void Engine::input()
{

	while (m_Window.pollEvent(event))
	{
		//Get mouse position
		mousePosition = sf::Vector2f(sf::Mouse::getPosition());
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;
		case Event::Resized:
			ResourseContainer.resizeTextures(sf::Vector2f(m_Window.getSize()));
			break;
		case sf::Event::MouseButtonPressed:
			savedPressLeftClickLocation = mousePosition;
			// If left button pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//Check popUpWindows
				if (showResearchWindow)
				{
					if (researchWindow.isClicked(mousePosition))
					{
						if (researchWindow.closeButton.isClicked(mousePosition))
						{
							showResearchWindow = false;
							break;
						}
						else
						{
							for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
							{
								if (researchWindow.technologyButtons[i].isClicked(mousePosition))
								{
									switch (i)
									{
										case int(TechnologyID::Sticks) :
											researchWindow.setTargetedResearch(TechnologyID::Sticks);
											break;

										case int(TechnologyID::Stones) :
											researchWindow.setTargetedResearch(TechnologyID::Stones);

											break;
										case int(TechnologyID::SticksAndStones) :
											researchWindow.setTargetedResearch(TechnologyID::SticksAndStones);
											break;
											default:break;
									}
									break;
								}
							}
						}
						if (researchWindow.selectResearchButton.isClicked(mousePosition)) 
						{
							researchWindow.setResearchToTargeted();
						}
					
						researchWindow.isGrabbed() = true;
						return;
						
					}
				}
				//Check interface buttons
				if (MouseState == MouseStates::NotOccupied)
				{
					// check if Building button is clicked
					for (int i = 0; i < AMOUNT_OF_BUILDING_BUTTONS; i++)
					{
						if (gameInterface.BuildingButtons[i].isClicked(mousePosition))
						{
							//SelectedBuildingType = BuildingType::turret;
							MouseState = MouseStates::build;
							switch (i)
							{
							case 0:
								SelectedBuilding = BuildingID::Turret1;
								break;
							case 1:
								SelectedBuilding = BuildingID::RocketLauncher1;
								break;
							case 2:
								SelectedBuilding = BuildingID::HangarBay1;
								break;
							case 3:
								SelectedBuilding = BuildingID::LaserTurret1;
								break;
								/*case 4:
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
					// check if ECONOMY button is clicked
					for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
					{
						if (gameInterface.economyButtons[i].isClicked(mousePosition))
						{
							//SelectedBuildingType = BuildingType::economy;
							MouseState = MouseStates::build;
							switch (i)
							{
							case 0:
								SelectedBuilding = BuildingID::EnergyGenerator;
								break;
							case 1:
								SelectedBuilding = BuildingID::MineralsGenerator;
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
					if (gameInterface.destroyButton.isClicked(mousePosition))
					{
						MouseState = MouseStates::destroy;
						//SelectedBuilding = BuildingID::none;
					}
					//Check research button
					if (gameInterface.researchButton.isClicked(mousePosition))
					{
						showResearchWindow = !showResearchWindow;
						SelectedBuilding = BuildingID::none;
						MouseState = MouseStates::NotOccupied;
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
							if (tileMap.lines[i].tiles[j].rec.contains(sf::Vector2i(mousePosition)))
							{
								tileMap.lines[i].tiles[j].placeBuilding(SelectedBuilding);


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
				{
					//Destory mode
					if (MouseState == MouseStates::destroy)
					{
						for (int i = 0; i < AMOUNT_OF_LINES; i++)
						{
							for (int j = 0; j < TILES_IN_A_LINE; j++)
							{
								if (tileMap.lines[i].tiles[j].building != nullptr)
								{
									if (tileMap.lines[i].tiles[j].rec.contains(sf::Vector2i(mousePosition)))
									{

										// if a buildong has a child then remove the child
										// else just remove building
										if (tileMap.lines[i].tiles[j].building->hasAChild)
										{
											tileMap.lines[i].tiles[j].removeBuilding();
											for (int k = 0; k < MAX_UNITS; k++)
											{
												if (UnitContainer.Units[k] != nullptr)
												{
													if (sf::Vector2i(i, j) == UnitContainer.Units[k]->parentIndex)
													{
														UnitContainer.destroy(k);
														return;
													}
												}
											}
										}
										else
										{
											tileMap.lines[i].tiles[j].removeBuilding();
											return;
										}
									}
								}
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
			//Left Button released
		case sf::Event::MouseButtonReleased:
			if (event.key.code == sf::Mouse::Left)
			{
				researchWindow.isGrabbed() = false;
				researchWindow.updateOriginalPosition();
			}
			break;
			//Check keyboard keys
			// If pressed
		case sf::Event::KeyPressed:

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
			if (event.key.code == sf::Keyboard::Q)
			{
				spawnEnemies = !spawnEnemies;
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