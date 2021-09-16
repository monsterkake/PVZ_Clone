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
	//interface
	TextureBackGround.loadFromFile("resourses/sprites/backGround_1.jpg");
	BackGround.setTexture(TextureBackGround);
	BackGround.setScale(sf::Vector2f((float)1920 / (float)TextureBackGround.getSize().x ,
		(float)1080 / (float)TextureBackGround.getSize().y));

	popUpWindowBase.loadFromFile("resourses/sprites/PopUpWindowBase.png");
	popUpWindowBaseSprite.setTexture(popUpWindowBase);

	buttonBase.loadFromFile("resourses/sprites/buttonBase.png");
	buttonBaseSprite.setTexture(buttonBase);
	// animations
	TextureAnimationTest.loadFromFile("resourses/animations/animationTest.png");
	AnimationTest.setTexture(TextureAnimationTest);
	AnimationTest.setScale(1, (float)TILESIZE / (float)TextureAnimationTest.getSize().y);
	


	//Buildings
	TextureAnimationHangarBay.loadFromFile("resourses/animations/buildings/animationHangarBay.png");
	TextureAnimationLaserTurret.loadFromFile("resourses/animations/buildings/animationLaserTurret.png");
	TextureAnimationRocketlauncher.loadFromFile("resourses/animations/buildings/animationRocketLauncher.png");
	TextureAnimationTurret.loadFromFile("resourses/animations/buildings/animationTurret.png");
	TextureAnimationEnergyGenerator.loadFromFile("resourses/animations/buildings/animationEnergyGenerator.png");
	TextureAnimationMineralsGenerator.loadFromFile("resourses/animations/buildings/animationMineralsGenerator.png");

	AnimationTurret.setTexture(TextureAnimationTurret);
	AnimationLaserTurret.setTexture(TextureAnimationLaserTurret);
	AnimationRocketlauncher.setTexture(TextureAnimationRocketlauncher);
	AnimationHangarBay.setTexture(TextureAnimationHangarBay);
	AnimationEnergyGenerator.setTexture(TextureAnimationEnergyGenerator);
	AnimationMineralsGenerator.setTexture(TextureAnimationMineralsGenerator);

	AnimationTurret.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationLaserTurret.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationRocketlauncher.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationHangarBay.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationEnergyGenerator.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationMineralsGenerator.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	//Projectiles
	TextureLaserBodyAnimation.loadFromFile("resourses/animations/projectiles/animationLaserBody.png");
	TextureAnimationRocket.loadFromFile("resourses/animations/projectiles/animationRocket.png");
	TextureAnimationBullet.loadFromFile("resourses/animations/projectiles/animationBullet.png");

	LaserBodyAnimation.setTexture(TextureLaserBodyAnimation);
	AnimationRocket.setTexture(TextureAnimationRocket);
	AnimationBullet.setTexture(TextureAnimationBullet);

	//AnimationRocket.setScale((float)PROJECTILE_SIZE / (float)SPRITE_SIZE, (float)PROJECTILE_SIZE / (float)SPRITE_SIZE);
	//enemies
	TextureAnimationScout.loadFromFile("resourses/animations/enemies/animationScout.png");
	TextureAnimationSwarmling.loadFromFile("resourses/animations/enemies/animationSwarmling.png");
	TextureAnimationAvoider.loadFromFile("resourses/animations/enemies/animationAvoider.png");

	AnimationScout.setTexture(TextureAnimationScout);
	AnimationSwarmling.setTexture(TextureAnimationSwarmling);
	AnimationAvoider.setTexture(TextureAnimationAvoider);

	AnimationScout.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationSwarmling.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
	AnimationAvoider.setScale((float)TILESIZE / (float)SPRITE_SIZE, (float)TILESIZE / (float)SPRITE_SIZE);
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

