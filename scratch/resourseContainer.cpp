#include "ResourseContainer.h"
#include <iostream>
#include "defValues.h"

using namespace std;


ResourseContainer::ResourseContainer()
{
	//font & text
	font.loadFromFile("resourses/fonts/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(13);

	// debug
	debugRect.setOutlineColor(sf::Color::Black);
	debugRect.setOutlineThickness(1);
	debugRect.setFillColor(sf::Color(0, 0, 0, 100));
	
	//sprites & textures
	greenRectTexture.loadFromFile("resourses/sprites/greenRect.png");
	redRectTexture.loadFromFile("resourses/sprites/redRect.png");
	blueRectTexture.loadFromFile("resourses/sprites/blueRect.png");

	greenRect.setTexture(greenRectTexture);
	greenRect.setScale((float)TILESIZE / (float)greenRectTexture.getSize().x , (float)TILESIZE / (float)greenRectTexture.getSize().y);
	greenRect.setColor(sf::Color(100, 100, 0, 100));

	redRect.setTexture(redRectTexture);
	redRect.setScale((float)PROJECTILE_SIZE / (float)redRectTexture.getSize().x, (float)PROJECTILE_SIZE / (float)redRectTexture.getSize().y);

	blueRect.setTexture(blueRectTexture);
	blueRect.setScale((float)TILESIZE / (float)redRectTexture.getSize().x, (float)TILESIZE / (float)redRectTexture.getSize().y);

	backGround.loadFromFile("resourses/sprites/background_1.jpg");
	backGroundSprite.setTexture(backGround);
	backGroundSprite.setScale(sf::Vector2f((float)1920 / (float)backGround.getSize().x ,
		(float)1080 / (float)backGround.getSize().y));
	// animations
	animationTest.loadFromFile("resourses/animations/animationTest.png");
	animationTestSprite.setTexture(animationTest);
	animationTestSprite.setScale(1, (float)TILESIZE / (float)animationTest.getSize().y);
	

	laserBodyAnimation.loadFromFile("resourses/animations/laserBodyAnimation.png");
	laserBodyAnimationSprite.setTexture(laserBodyAnimation);
}

Vector2f ResourseContainer::getResizeCoeffitient()
{
	return Vector2f(resizeCoeffitient);
}

void ResourseContainer::resizeTextures(Vector2f newResolution)
{

	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	//resizeCoeffitient.x = resolution.x / 1920;
	//resizeCoeffitient.y = resolution.y / 1080;

	//greenRect.setSize(sf::Vector2f(TILESIZE, TILESIZE));
	//redRect.setSize(sf::Vector2f(TILESIZE / 2, TILESIZE / 2));

	//std::cout << resolution.x << endl;
}

void ResourseContainer::setResolution(Vector2f resolution)
{
	this->resolution = resolution;
}

