#include "Player.h"
#include "Utils.h"

Player::Player()
{
	shape.setRadius(RADIUS);
	shape.setOrigin({ RADIUS, RADIUS });
	reset();
}

/// <summary>
/// Сбрасывает игрока
/// </summary>
void Player::reset()
{
	shape.setPosition({ 50.f, 50.f });
	shape.setFillColor(sf::Color::Green);
}

/// <summary>
/// Изменение Player в каждом кадре
/// </summary>
/// <param name="dt"></param>
/// <param name="level"></param>
void Player::update(float dt, Level& level) 
{
    sf::Vector2f dir(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dir.x += 1.f;

    if (Geometry::getLength(dir) > 0) {
        sf::Vector2f velocity = Geometry::normalize(dir) * PLAYER_SPEED * dt;

        // По оси X
        shape.move({ velocity.x, 0.f });
        if (level.checkCollision(shape.getGlobalBounds()))
            shape.move({ -velocity.x, 0.f });

        // По оси Y
        shape.move({ 0.f, velocity.y });
        if (level.checkCollision(shape.getGlobalBounds()))
            shape.move({ 0.f, -velocity.y });
    }
}

/// <summary>
/// Отрисовка Player в игровом окне
/// </summary>
/// <param name="window"></param>
void Player::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}