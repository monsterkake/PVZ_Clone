#include <SFML/Graphics.hpp>

using namespace sf;



class ResourseContainer
{
    Vector2f resizeCoeffitient;
    Vector2f resolution;

    sf::Texture greenRectTexture;
    sf::Texture redRectTexture;
    sf::Texture blueRectTexture;

    sf::Texture laserBodyAnimation;

    sf::Texture backGround;

    sf::Texture animationTest;
    public:
    
    sf::Font font;
    sf::Text text;

    std::string string;// String for conversion

    sf::RectangleShape debugRect;

    sf::Sprite greenRect;
    sf::Sprite redRect;
    sf::Sprite blueRect;


    sf::Sprite backGroundSprite;

    sf::Sprite animationTestSprite;
    
    sf::Sprite laserBodyAnimationSprite;

    ResourseContainer();
    Vector2f getResizeCoeffitient();
    void resizeTextures(Vector2f newResolution);
    void setResolution(Vector2f resolution);
};

