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
				/*ResourseContainer.redRect.setPosition
				(enemyContainer->enemy[
					enemyContainer->indexOfClosestEnemyInLine[
						ProjectileContainer.projectiles[i]->line]]->getPosition());*/
				if (enemyContainer->getClosestEnemyInLine(ProjectileContainer.projectiles[i]->line) != nullptr)
				{
					ResourseContainer.LaserBodyAnimation.setTextureRect(ProjectileContainer.projectiles[i]->getFrame());
					ResourseContainer.LaserBodyAnimation.setPosition(ProjectileContainer.projectiles[i]->getPosition());

					ResourseContainer.LaserBodyAnimation.setScale(sf::Vector2f((
						enemyContainer->getClosestEnemyInLine(ProjectileContainer.projectiles[i]->line)->getPosition().x -
						ProjectileContainer.projectiles[i]->getPosition().x) / SPRITE_SIZE, 1));

					renderTexture.draw(ResourseContainer.LaserBodyAnimation);
				}
				


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
		if (enemyContainer->enemy[i] != nullptr)
		{

			switch (enemyContainer->enemy[i]->id)
			{
			case EnemyID::Scout:

				ResourseContainer.AnimationTest.setTextureRect(enemyContainer->enemy[i]->getFrame());
				ResourseContainer.AnimationTest.setPosition(enemyContainer->enemy[i]->getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);

				break;
			case EnemyID::Swarmling:
				ResourseContainer.AnimationTest.setTextureRect(enemyContainer->enemy[i]->getFrame());
				ResourseContainer.AnimationTest.setPosition(enemyContainer->enemy[i]->getPosition());
				renderTexture.draw(ResourseContainer.AnimationTest);
				break;
			default:break;
			}
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(enemyContainer->enemy[i]->getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(enemyContainer->enemy[i]->getBoundRect().width,
					enemyContainer->enemy[i]->getBoundRect().height));
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
			case UnitID::Fighter1:
				ResourseContainer.redRect.setPosition(UnitContainer.Units[i]->getPosition());
				renderTexture.draw(ResourseContainer.redRect);
				break;
			default:break;
			}
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(enemyContainer->enemy[i]->getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(enemyContainer->enemy[i]->getBoundRect().width,
					enemyContainer->enemy[i]->getBoundRect().height));
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

