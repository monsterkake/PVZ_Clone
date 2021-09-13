#include "engine.h"


Engine::Engine()
{
    // Получаем разрешение экрана, создаем окно SFML и View
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    ResourseContainer.setResolution(resolution);
    //ResourseContainer.resizeTextures(sf::Vector2f(m_Window.getSize()));
    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Simple Game Engine",
        Style::Fullscreen);
 
    renderTexture.create(resolution.x, resolution.y);
    enemyContainer = std::shared_ptr<EnemyContainer>(new EnemyContainer);
    UnitContainer.enemyContainer = enemyContainer;
}

void Engine::start()
{
    // Расчет времени
    Clock clock;

    while (m_Window.isOpen())
    {
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}