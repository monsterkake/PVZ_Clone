#include "engine.h"
//#include "gameinterface.h"
#include "BuildingID.h"

sf::Clock DrawClock;

bool DrawFPSmeasuring = false;

void Engine::draw()
{
	if (DrawFPSmeasuring)
	{
		DrawClock.restart();
	}
	
	
	// Clear Window
	m_Window.clear(Color::White);
	renderTexture.clear();
	//Draw TextureBackGround
	renderTexture.draw(ResourseContainer.BackGround);
	//Draw Tiles
	renderTexture.draw(tileMap.getSprite());
	for (int i = 0; i < AMOUNT_OF_LINES; i++)
	{
		for (int j = 0; j < TILES_IN_A_LINE; j++)
		{
			//Draw Buildings
			if (tileMap.lines[i].tiles[j].building != nullptr)
			{
				switch (tileMap.lines[i].tiles[j].building->id)
				{
				case BuildingID::Turret1:
					ResourseContainer.AnimationTurret.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationTurret.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationTurret);
					break;
				case BuildingID::RocketLauncher1:
					ResourseContainer.AnimationRocketlauncher.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationRocketlauncher.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationRocketlauncher);
					break;
				case BuildingID::HangarBay1:
					ResourseContainer.AnimationHangarBay.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationHangarBay.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationHangarBay);
					break;
				case BuildingID::LaserTurret1:
					ResourseContainer.AnimationLaserTurret.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationLaserTurret.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationLaserTurret);
					break;
				case BuildingID::EnergyGenerator:
					ResourseContainer.AnimationEnergyGenerator.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationEnergyGenerator.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationEnergyGenerator);
					break;
				case BuildingID::MineralsGenerator:
					ResourseContainer.AnimationMineralsGenerator.setTextureRect(tileMap.lines[i].tiles[j].building->getFrame());
					ResourseContainer.AnimationMineralsGenerator.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
					renderTexture.draw(ResourseContainer.AnimationMineralsGenerator);
					break;
				default:
					break;
				}
			}

		}
	}

	//Draw Interface
	//Draw Building Buttons
	gameInterface.updateSprite(mousePosition,resourseEnergy,resourseMinerals);
	renderTexture.draw(gameInterface.getSprite());
	//ResourseContainer.buttonBaseSprite.setScale(0.5, 0.5);
	//for (int i = 0; i < AMOUNT_OF_BUILDING_BUTTONS; i++)
	//{
	//	ResourseContainer.buttonBaseSprite.setPosition(gameInterface.BuildingButtons[i].getPosition());
	//	renderTexture.draw(ResourseContainer.buttonBaseSprite);
	//	renderTexture.draw(gameInterface.BuildingButtons[i].getText());
	//}
	////Draw economy Buttons
	//for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
	//{
	//	ResourseContainer.buttonBaseSprite.setPosition(gameInterface.economyButtons[i].getPosition());
	//	renderTexture.draw(ResourseContainer.buttonBaseSprite);
	//	renderTexture.draw(gameInterface.economyButtons[i].getText());
	//}

	////Draw destroy button
	//ResourseContainer.buttonBaseSprite.setPosition(gameInterface.destroyButton.getPosition());
	//renderTexture.draw(ResourseContainer.buttonBaseSprite);
	//renderTexture.draw(gameInterface.destroyButton.getText());

	////Draw research button
	//ResourseContainer.buttonBaseSprite.setPosition(gameInterface.researchButton.getPosition());
	//renderTexture.draw(ResourseContainer.buttonBaseSprite);
	//renderTexture.draw(gameInterface.researchButton.getText());

	////return sprite scale to normal
	//ResourseContainer.buttonBaseSprite.setScale(1, 1);

	////Draw labels
	//gameInterface.energyLabel.setText(std::string(": " + std::to_string(resourseEnergy)));
	//renderTexture.draw(gameInterface.energyLabel.getText());
	//gameInterface.mineralsLabel.setText(std::string(": " + std::to_string(resourseMinerals)));
	//renderTexture.draw(gameInterface.mineralsLabel.getText());

	//Draw Projectiles
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (ProjectileContainer.projectiles[i] != nullptr)
		{
			switch (ProjectileContainer.projectiles[i]->id)
			{
			case ProjectileID::Bullet1:
				ResourseContainer.AnimationBullet.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				ResourseContainer.AnimationBullet.setTextureRect(ProjectileContainer.projectiles[i]->getFrame());
				renderTexture.draw(ResourseContainer.AnimationBullet);
				break;
			case ProjectileID::Rocket1:
				ResourseContainer.AnimationRocket.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				ResourseContainer.AnimationRocket.setTextureRect(ProjectileContainer.projectiles[i]->getFrame());
				ResourseContainer.AnimationRocket.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE / 2);

				ResourseContainer.AnimationRocket.setRotation(ProjectileContainer.projectiles[i]->getAngle() + 90);

				renderTexture.draw(ResourseContainer.AnimationRocket);
				break;
			case ProjectileID::Laser1:
				ResourseContainer.redRect.setPosition
				(UnitContainer.enemyContainer.enemy[
					UnitContainer.enemyContainer.indexOfClosestEnemyInLine[
						ProjectileContainer.projectiles[i]->line]].getPosition());

				ResourseContainer.LaserBodyAnimation.setTextureRect(ProjectileContainer.projectiles[i]->getFrame());
				ResourseContainer.LaserBodyAnimation.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				
				ResourseContainer.LaserBodyAnimation.setScale(sf::Vector2f((
					UnitContainer.enemyContainer.enemy[
						UnitContainer.enemyContainer.indexOfClosestEnemyInLine[
							ProjectileContainer.projectiles[i]->line]].getPosition().x -
								ProjectileContainer.projectiles[i]->getPosition().x) / SPRITE_SIZE,1 ));
				renderTexture.draw(ResourseContainer.LaserBodyAnimation);


				break;
			default:
				break;
			}
			
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(ProjectileContainer.projectiles[i]->getBoundRect().width,
					ProjectileContainer.projectiles[i]->getBoundRect().height));
				renderTexture.draw(ResourseContainer.debugRect);
			}

		}
	}
	//Draw Enemies
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (UnitContainer.enemyContainer.enemy[i].id != UnitID::none)
		{

			switch (UnitContainer.enemyContainer.enemy[i].id)
			{
			case UnitID::e0:

				ResourseContainer.AnimationTest.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.AnimationTest.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);

				break;
			case UnitID::e1:
				ResourseContainer.AnimationTest.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.AnimationTest.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);
				break;
			default:break;
			}
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(UnitContainer.enemyContainer.enemy[i].getBoundRect().width,
					UnitContainer.enemyContainer.enemy[i].getBoundRect().height));
				renderTexture.draw(ResourseContainer.debugRect);
			}
		}
	}
	//Draw Units
	 for (int i = 0; i < MAX_UNITS; i++)
	 {
		if (UnitContainer.Units[i] != nullptr)
		{

			switch (UnitContainer.Units[i]->id)
			{
			case UnitID::e0:

				ResourseContainer.AnimationTest.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.AnimationTest.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);
				break;
			case UnitID::e1:
				ResourseContainer.AnimationTest.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.AnimationTest.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);
				break;
			case UnitID::Fighter1:
				ResourseContainer.redRect.setPosition(UnitContainer.Units[i]->getPosition());
				renderTexture.draw(ResourseContainer.redRect);
				break;
			default:break;
			}
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(UnitContainer.enemyContainer.enemy[i].getBoundRect().width,
					UnitContainer.enemyContainer.enemy[i].getBoundRect().height));
				renderTexture.draw(ResourseContainer.debugRect);
			}
		}
	}
	 //Draw popUp windows
	 //Draw research window
	 if (showResearchWindow) 
	 {
		 //researchWindow.updateWidgets(mousePosition);
		 researchWindow.updateSprite(mousePosition);
		 renderTexture.draw(researchWindow.getSprite());
	 }

	// Display everything
	renderTexture.display();
	renderTexture.generateMipmap();
	renderSprite.setTexture(renderTexture.getTexture());

	m_Window.draw(renderSprite);
	m_Window.display();

	if (DrawFPSmeasuring)
	{
		std::cout << DrawClock.getElapsedTime().asSeconds() << std::endl;
	}
}

