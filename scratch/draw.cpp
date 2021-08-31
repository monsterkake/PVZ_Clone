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
	
	
	// ������� ���������� ����
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
			if (tileMap.lines[i].tiles[j].Building.id != BuildingID::none)
			{
				ResourseContainer.blueRect.setPosition(tileMap.lines[i].tiles[j].Building.getPosition());
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
		if (ProjectileContainer.Projectiles[i].id != ProjectileID::none)
		{
			ResourseContainer.redRect.setPosition(ProjectileContainer.Projectiles[i].getPosition());
			renderTexture.draw(ResourseContainer.redRect);
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(ProjectileContainer.Projectiles[i].getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(ProjectileContainer.Projectiles[i].getBoundRect().width,
					ProjectileContainer.Projectiles[i].getBoundRect().height));
				renderTexture.draw(ResourseContainer.debugRect);
			}

		}
	}
	//Draw Enemies
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (EnemyContainer.enemy[i].id != EnemyID::none)
		{


			switch (EnemyContainer.enemy[i].id)
			{
			case EnemyID::e0:
				ResourseContainer.animationTestSprite.setTextureRect(EnemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(EnemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);

				break;
			case EnemyID::e1:
				ResourseContainer.animationTestSprite.setTextureRect(EnemyContainer.enemy[i].getFrame());
				ResourseContainer.animationTestSprite.setPosition(EnemyContainer.enemy[i].getPosition());
				renderTexture.draw(ResourseContainer.animationTestSprite);
				break;
			default:break;
			}
			// draw debug rect
			if (DebugMode)
			{
				ResourseContainer.debugRect.setPosition(EnemyContainer.enemy[i].getPosition());
				ResourseContainer.debugRect.setSize(sf::Vector2f(EnemyContainer.enemy[i].getBoundRect().width,
					EnemyContainer.enemy[i].getBoundRect().height));
				renderTexture.draw(ResourseContainer.debugRect);
			}
		}
	}
	//sf::Sprite sprite;
	//sf::tex
	// ���������� ���, ��� ����������

	renderTexture.display();
	
	renderSprite.setTexture(renderTexture.getTexture());

	m_Window.draw(renderSprite);
	m_Window.display();

	if (DrawFPSmeasuring)
	{
		std::cout << DrawClock.getElapsedTime().asSeconds() << std::endl;
	}
}

