#include <SFML/Graphics.hpp>

using namespace sf;



class ResourseContainer
{
    Vector2f resizeCoeffitient;
    Vector2f resolution;

    sf::Texture greenRectTexture;
    sf::Texture redRectTexture;
    sf::Texture blueRectTexture;



    sf::Texture TextureBackGround;

    sf::Texture TextureAnimationTest;

    sf::Texture popUpWindowBase;

    sf::Texture buttonBase;
    //Buildings
    sf::Texture TextureAnimationTurret;
    sf::Texture TextureAnimationRocketlauncher;
    sf::Texture TextureAnimationHangarBay;
    sf::Texture TextureAnimationLaserTurret;
    sf::Texture TextureAnimationEnergyGenerator;
    sf::Texture TextureAnimationMineralsGenerator;
    //Projectiles
    sf::Texture TextureAnimationRocket;
    sf::Texture TextureLaserBodyAnimation;
    sf::Texture TextureAnimationBullet;
    public:
    
    sf::Font font;
    sf::Text text;

    std::string string;// String for conversion

    sf::RectangleShape debugRect;

    sf::Sprite greenRect;
    sf::Sprite redRect;
    sf::Sprite blueRect;


    sf::Sprite BackGround;

    sf::Sprite AnimationTest;
    


    sf::Sprite popUpWindowBaseSprite;

    sf::Sprite buttonBaseSprite;
    //Buildings
    sf::Sprite AnimationTurret;
    sf::Sprite AnimationRocketlauncher;
    sf::Sprite AnimationHangarBay;
    sf::Sprite AnimationLaserTurret;
    sf::Sprite AnimationEnergyGenerator;
    sf::Sprite AnimationMineralsGenerator;
    //projectiles
    sf::Sprite AnimationRocket;
    sf::Sprite LaserBodyAnimation;
    sf::Sprite AnimationBullet;

    ResourseContainer();
    Vector2f getResizeCoeffitient();
    void resizeTextures(Vector2f newResolution);
    void setResolution(Vector2f resolution);
};

