#include "engine.h"


Engine::Engine()
{
    // �������� ���������� ������, ������� ���� SFML � View
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    ResourseContainer.setResolution(resolution);
    ResourseContainer.resizeTextures(sf::Vector2f(m_Window.getSize()));
    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Simple Game Engine",
        Style::Fullscreen);

}

void Engine::start()
{
    // ������ �������
    Clock clock;

    while (m_Window.isOpen())
    {
        // ������������� ������ � ���������� ���������� ����� � dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}