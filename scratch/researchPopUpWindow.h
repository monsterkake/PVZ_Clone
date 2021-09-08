#pragma once
#include "popUpWindow.h"
#include "techTree.h"
#include "label.h"

#define DESCRIPTION_SIZE_X 0.2
#define DESCRIPTION_SIZE_Y 1

class ResearchPopUpWindow : public PopUpWindow, public HasACooldown
{
	sf::Texture buttonBase;
	sf::Texture closeButtonBase;
	sf::Sprite buttonBaseSprite;
	sf::Sprite closeButtonBaseSprite;

	sf::Texture TextureDescriptionBase;
	sf::Sprite descriptionBase;

	sf::RectangleShape progressRectangle;

	std::shared_ptr<TechnologyID> currentResearch;
	//TechnologyID selectedResearch = TechnologyID::none;
	TechnologyID targetedResearch = TechnologyID::none;
	sf::Color clickedColor = sf::Color(50, 200, 50, 255);
	sf::Color hoveredColor = sf::Color(200, 200, 200, 255);
	sf::Color notHoveredColor = sf::Color(150, 150, 150, 255);
public:
	

	TechnologyTree techTree;

	Button closeButton;

	Button technologyButtons[TECHNOLOGY_TREE_LENGTH];

	Button selectResearchButton;

	Label progressBar;

	Label techDescription;
	ResearchPopUpWindow()
	{
		// initialize current research
		currentResearch = std::shared_ptr<TechnologyID>(new TechnologyID);
		*currentResearch = TechnologyID::none;
		//Textures to sprites
		closeButtonBase.loadFromFile("resourses/sprites/closeButtonBase.png");
		closeButtonBaseSprite.setTexture(closeButtonBase);
		closeButtonBaseSprite.setScale(0.2, 0.2);

		buttonBase.loadFromFile("resourses/sprites/buttonBase.png");
		buttonBaseSprite.setTexture(buttonBase);
		buttonBaseSprite.setScale(1, 0.5);

		TextureDescriptionBase.loadFromFile("resourses/sprites/PopUpWindowBase.png");
		descriptionBase.setTexture(TextureDescriptionBase);
		descriptionBase.setScale(popUpWindowBaseSprite.getScale().x * DESCRIPTION_SIZE_X, popUpWindowBaseSprite.getScale().y * DESCRIPTION_SIZE_Y);
		//rectangle for progress configure
		progressRectangle.setFillColor(sf::Color(0,255,0,100));
		progressRectangle.setSize(sf::Vector2f(100,50));
		//what am i doing with my life?
		m_isGrabbed = std::shared_ptr<bool>(new bool);
		*m_isGrabbed = false;
		//collision configure

		size = sf::Vector2f(1000, 500);
		boundRect.height = size.y;
		boundRect.width = size.x;
		popUpWindowBase.loadFromFile("resourses/sprites/PopUpWindowBase.png");
		popUpWindowBaseSprite.setTexture(popUpWindowBase);
		popUpWindowBaseSprite.setScale(size.x / SPRITE_SIZE, size.y / SPRITE_SIZE);
		name.setText("ResearchWindow");
		name.setPosition(sf::Vector2f(0, 0));
		name.setOffset();
		// draw base and text
		m_renderTexture.draw(popUpWindowBaseSprite);
		m_renderTexture.draw(name.getText());


		//position configure
		setPosition(sf::Vector2f(0, 0));
		updateOriginalPosition();
		//configure widgets
		closeButton.setBoundRect(sf::FloatRect(0, 0, SPRITE_SIZE / 5, SPRITE_SIZE / 5));
		closeButton.setPosition(sf::Vector2f(this->getPosition().x + size.x - SPRITE_SIZE / 5, this->getPosition().y));
		closeButton.setOffset();

		selectResearchButton.setBoundRect(sf::FloatRect(0, 0, 100, 50));
		selectResearchButton.setPosition(sf::Vector2f(50, size.y - buttonBaseSprite.getScale().y * SPRITE_SIZE - 20));
		selectResearchButton.setText("select");
		selectResearchButton.setOffset();
		

		for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
		{
			technologyButtons[i].setBoundRect(sf::FloatRect(0,0,100,50));
		}

		technologyButtons[int(TechnologyID::Sticks)].setText("Sticks");
		technologyButtons[int(TechnologyID::Stones)].setText("Stones");
		technologyButtons[int(TechnologyID::SticksAndStones)].setText("SticksAndStones");

		technologyButtons[int(TechnologyID::Sticks)].setPosition(sf::Vector2f(300,100));
		technologyButtons[int(TechnologyID::Stones)].setPosition(sf::Vector2f(300, 200));
		technologyButtons[int(TechnologyID::SticksAndStones)].setPosition(sf::Vector2f(500, 150));

		technologyButtons[int(TechnologyID::Sticks)].setOffset();
		technologyButtons[int(TechnologyID::Stones)].setOffset();
		technologyButtons[int(TechnologyID::SticksAndStones)].setOffset();

		progressBar.setPosition(sf::Vector2f(10, 400));
		progressBar.setStringBase("progress");
		progressBar.setOffset();

		techDescription.setPosition(sf::Vector2f(10, 30));
		techDescription.setStringBase("Description:");
		techDescription.setOffset();

		//Draw 
		updateSprite(sf::Vector2f(0,0));
		//test

		//update Sprite
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
	}

	void update(sf::Vector2f mpos, float researchIncome, float dtAsSeconds)
	{
		//update research
		if (getCurrentResearch() != TechnologyID::none)
			if(cooldownIsReady(dtAsSeconds))
				techTree.technologies[int(getCurrentResearch())].addPoints(researchIncome);
	}

	//void updateWidgets(sf::Vector2f mpos) 
	//{
	//	for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
	//	{
	//		if()
	//		technologyButtons[i].getText().setPosition(technologyButtons[i].getPosition() - this->getPosition());


	//	}
	//}

	void updateSprite(sf::Vector2f mpos)
	{
		m_renderTexture.clear(sf::Color(0,0,0,0));
		//m_sprite->setPosition(0,0);
		m_renderTexture.draw(popUpWindowBaseSprite);

		if (closeButton.isHovered(mpos))
		{
			closeButtonBaseSprite.setColor(hoveredColor);
			
		}
		else
		{
			closeButtonBaseSprite.setColor(notHoveredColor);
		}
		closeButtonBaseSprite.setPosition(closeButton.getPosition() - this->getPosition());
		m_renderTexture.draw(closeButtonBaseSprite);
		//draw technology buttons
		//savedColor = buttonBaseSprite.getColor();
		for (int i = 0; i < TECHNOLOGY_TREE_LENGTH; i++)
		{
			if (technologyButtons[i].isHovered(mpos)) 
			{
				buttonBaseSprite.setColor(hoveredColor);
			}
			else 
			{
				if (int(targetedResearch) == i)
				{
					buttonBaseSprite.setColor(clickedColor);
				}
				else
				{
					buttonBaseSprite.setColor(notHoveredColor);
				}
			}
			
			buttonBaseSprite.setPosition(technologyButtons[i].getPosition() - this->getPosition());
			m_renderTexture.draw(buttonBaseSprite);
			technologyButtons[i].getText().setPosition(technologyButtons[i].getPosition() - this->getPosition());

			progressRectangle.setPosition(technologyButtons[i].getPosition() - this->getPosition());
			progressRectangle.setSize(sf::Vector2f(100 * techTree.technologies[i].getProgressPercentage(), 50));
			m_renderTexture.draw(technologyButtons[i].getText());

			m_renderTexture.draw(progressRectangle);
			
		}

		//draw info panel
		
		m_renderTexture.draw(descriptionBase);

		if (selectResearchButton.isHovered(mpos))
		{
			buttonBaseSprite.setColor(hoveredColor);
		}
		else
		{
			buttonBaseSprite.setColor(notHoveredColor);
		}
		buttonBaseSprite.setPosition(selectResearchButton.getPosition() - this->getPosition());
		m_renderTexture.draw(buttonBaseSprite);
		selectResearchButton.getText().setPosition(selectResearchButton.getPosition() - this->getPosition());
		m_renderTexture.draw(selectResearchButton.getText());

		//draw progress bar
		progressBar.setText(std::to_string(int(techTree.technologies[int(targetedResearch)].getProgressPercentage() * 100)) + "%");
		m_renderTexture.draw(progressBar.getText());
		//draw tech description
		if (int(targetedResearch) < TECHNOLOGY_TREE_LENGTH) 
		{
			techDescription.setText(techTree.technologies[int(targetedResearch)].description);
			m_renderTexture.draw(techDescription.getText());
		}
		
		//test
		//draw window name
		m_renderTexture.draw(name.getText());
		//update Sprite
		m_renderTexture.display();
		m_sprite->setTexture(m_renderTexture.getTexture());
	}

	void setPosition(sf::Vector2f position) override
	{
		this->position = position;
		m_sprite->setPosition(this->position);
		boundRect.left = position.x;
		boundRect.top = position.y;
		closeButton.setPosition(this->getPosition());
		selectResearchButton.setPosition(this->getPosition());
		technologyButtons[int(TechnologyID::Sticks)].setPosition(this->getPosition() );
		technologyButtons[int(TechnologyID::Stones)].setPosition(this->getPosition() );
		technologyButtons[int(TechnologyID::SticksAndStones)].setPosition(this->getPosition() );
		
	}

	void setResearchToTargeted()
	{
		if (techTree.requirementsIsReached(targetedResearch))
		{
			*currentResearch = targetedResearch;
		}
	}
	void setTargetedResearch(TechnologyID research)
	{
		targetedResearch = research;
	}
	TechnologyID getTargetedResearch() 
	{
		return targetedResearch;
	}
	TechnologyID getCurrentResearch() 
	{
		return *currentResearch;
	}
};