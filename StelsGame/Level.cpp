#include "Level.h"

Level::Level()
{
    goal.setSize({ 60.f, 60.f });
    goal.setPosition({ 720.f, 520.f });
    goal.setFillColor(sf::Color::Blue);

    createWall(200, 150, 20, 300);
    createWall(400, 100, 200, 20);
    createWall(500, 350, 50, 50);
}

/// <summary>
/// Добавляет стену в vector класса Level
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
void Level::createWall(float x, float y, float w, float h)
{
    sf::RectangleShape wall({ w, h });
    wall.setPosition({ x, y });
    wall.setFillColor(sf::Color(80, 80, 80));
    walls.push_back(wall);
}

/// <summary>
/// Рендерит стены на окне
/// </summary>
/// <param name="window"></param>
void Level::draw(sf::RenderWindow& window) 
{
    window.draw(goal);
    for (auto& wall : walls)
    {
        window.draw(wall);
    }
}

/// <summary>
/// Проверяет коллизию bounds со всеми стенами
/// </summary>
/// <param name="bounds"></param>
/// <returns></returns>
bool Level::checkCollision(sf::FloatRect bounds) 
{
    for (auto& wall : walls) {
        if (bounds.findIntersection(wall.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}