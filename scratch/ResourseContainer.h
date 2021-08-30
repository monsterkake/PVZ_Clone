#include <SFML/Graphics.hpp>

using namespace sf;



class ResourseContainer
{
    Vector2f resizeCoeffitient;
    Vector2f resolution;
    public:
    
    sf::Font font;
    sf::Text text;

    std::string string;// String for conversion

    sf::RectangleShape debugRect;

    sf::Texture greenRectTexture;
    sf::Texture redRectTexture;
    sf::Texture blueRectTexture;

    sf::Sprite greenRect;
    sf::Sprite redRect;
    sf::Sprite blueRect;

    sf::Texture backGround;
    sf::Sprite backGroundSprite;

    sf::Texture animationTest;
    sf::Sprite animationTestSprite;
    


    ResourseContainer();
    Vector2f getResizeCoeffitient();
    void resizeTextures(Vector2f newResolution);
    void setResolution(Vector2f resolution);
};

