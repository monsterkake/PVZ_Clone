#include "engine.h"
//#include "gameinterface.h"

sf::Clock DrawClock;

bool DrawFPSmeasuring = false;




void Engine::draw()
{
	if (DrawFPSmeasuring)
	{
		DrawClock.restart();
	}
	
	
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);
	renderTexture.clear();
	//Draw Background
	renderTexture.draw(ResourseContainer.backGroundSprite);
	//Draw Tiles
	for (int i = 0; i < AMOUNT_OF_LINES; i++)
	{
		for (int j = 0; j < TILES_IN_A_LINE; j++)
		{
			ResourseContainer.greenRect.setPosition(tileMap.lines[i].tiles[j].getPosition());

			renderTexture.draw(ResourseContainer.greenRect);
			//Draw Buildings
			if (tileMap.lines[i].tiles[j].building != nullptr)
			{
				ResourseContainer.blueRect.setPosition(tileMap.lines[i].tiles[j].building->getPosition());
				renderTexture.draw(ResourseContainer.blueRect);
			}

		}
	}

	//Draw Interface
	//Draw Building Buttons
	for (int i = 0; i < AMOUNT_OF_Building_BUTTONS; i++)
	{
		renderTexture.draw(gameInterface.BuildingButtons[i].getTexture());
		ResourseContainer.text.setString(gameInterface.BuildingButtons[i].getString());
		ResourseContainer.text.setPosition(gameInterface.BuildingButtons[i].getPosition() + sf::Vector2f(0, 60));
		renderTexture.draw(ResourseContainer.text);
	}
	//Draw economy Buttons
	for (int i = 0; i < AMOUNT_OF_ECONOMY_BUTTONS; i++)
	{
		renderTexture.draw(gameInterface.economyButtons[i].getTexture());
		ResourseContainer.text.setString(gameInterface.economyButtons[i].getString());
		ResourseContainer.text.setPosition(gameInterface.economyButtons[i].getPosition() + sf::Vector2f(0, 60));
		renderTexture.draw(ResourseContainer.text);
	}

	//Draw destroy button
	ResourseContainer.text.setString(gameInterface.destroyButton.getString());
	ResourseContainer.text.setPosition(gameInterface.destroyButton.getPosition() + sf::Vector2f(0, 60));
	renderTexture.draw(gameInterface.destroyButton.getTexture());
	renderTexture.draw(ResourseContainer.text);

	//Draw labels

	ResourseContainer.string.append(gameInterface.energyLabel.getString() + ": " + std::to_string(resourseEnergy));
	ResourseContainer.text.setString(ResourseContainer.string);
	ResourseContainer.text.setPosition(gameInterface.energyLabel.getPosition());
	renderTexture.draw(ResourseContainer.text);
	ResourseContainer.string.clear();

	ResourseContainer.string.append(gameInterface.mineralsLabel.getString() + ": " + std::to_string(resourseMinerals));
	ResourseContainer.text.setString(ResourseContainer.string);
	ResourseContainer.text.setPosition(gameInterface.mineralsLabel.getPosition());
	renderTexture.draw(ResourseContainer.text);
	ResourseContainer.string.clear();

	//Draw Projectiles
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (ProjectileContainer.projectiles[i] != nullptr)
		{
			switch (ProjectileContainer.projectiles[i]->id)
			{
			case ProjectileID::Bullet1:
				ResourseContainer.redRect.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				renderTexture.draw(ResourseContainer.redRect);
				break;
			case ProjectileID::Rocket1:
				ResourseContainer.redRect.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				renderTexture.draw(ResourseContainer.redRect);
				break;
			case ProjectileID::Laser1://
				//ResourseContainer.redRect.setPosition(ProjectileContainer.projectiles[i]->getPosition());
				ResourseContainer.redRect.setPosition
				(UnitContainer.enemyContainer.enemy[
					UnitContainer.enemyContainer.indexOfClosestEnemyInLine[
						ProjectileContainer.projectiles[i]->line]].getPosition());
				//ResourseContainer.redRect.setScale
				renderTexture.draw(ResourseContainer.redRect);
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

				ResourseContainer.animationTestSprite.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);

				break;
			case UnitID::e1:
				ResourseContainer.animationTestSprite.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);
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

				ResourseContainer.animationTestSprite.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);

				break;
			case UnitID::e1:
				ResourseContainer.animationTestSprite.setTextureRect(UnitContainer.enemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(UnitContainer.enemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);
				break;
			case UnitID::Fighter1:
				//ResourseContainer.blueRect.setTextureRect(UnitContainer.Units[i]->.getFrame());
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

