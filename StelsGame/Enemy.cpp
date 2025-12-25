#include "Enemy.h"
#include "Utils.h"

Enemy::Enemy(std::vector<sf::Vector2f> p) : path(p) {
    shape.setPointCount(3);
    shape.setPoint(0, { 20.f, 0.f });
    shape.setPoint(1, { -15.f, 15.f });
    shape.setPoint(2, { -15.f, -15.f });
    shape.setFillColor(sf::Color::Red);
    if (!path.empty()) shape.setPosition(path[0]);
}

/// <summary>
/// Покадровое обновление противника
/// </summary>
/// <param name="dt"></param>
void Enemy::update(float dt) 
{
    if (path.empty()) return;

    sf::Vector2f target = path[pathIndex];
    sf::Vector2f toTarget = target - shape.getPosition();

    if (Geometry::getLength(toTarget) < 5.f) 
    {
        pathIndex = (pathIndex + 1) % path.size();
    }
    else 
    {
        sf::Vector2f dir = Geometry::normalize(toTarget);
        shape.move(dir * ENEMY_SPEED * dt);
        float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159f;
        shape.setRotation(sf::degrees(angle));
    }
}

/// <summary>
/// Проверяет видит ли противник игрока
/// </summary>
/// <param name="playerPos"></param>
/// <param name="walls"></param>
void Enemy::checkVision(sf::Vector2f playerPos, std::vector<sf::RectangleShape>& walls) 
{
    seesPlayer = false;
    sf::Vector2f enemyPos = shape.getPosition();
    sf::Vector2f toPlayer = playerPos - enemyPos;

    if (Geometry::getLength(toPlayer) > VIEW_DISTANCE)
    {
        return;
    }

    sf::Vector2f dirToPlayer = Geometry::normalize(toPlayer);
    float rad = shape.getRotation().asRadians();
    sf::Vector2f facing({ std::cos(rad), std::sin(rad) });

    if ((dirToPlayer.x * facing.x + dirToPlayer.y * facing.y) < std::cos(VIEW_ANGLE * DEG_TO_RAD))
    {
        return;
    }

    for (const auto& wall : walls) 
    {
        sf::FloatRect b = wall.getGlobalBounds();
        sf::Vector2f p1(b.position.x, b.position.y);
        sf::Vector2f p2(b.position.x + b.size.x, b.position.y);
        sf::Vector2f p3(b.position.x + b.size.x, b.position.y + b.size.y);
        sf::Vector2f p4(b.position.x, b.position.y + b.size.y);

        if (Geometry::checkIntersection(enemyPos, playerPos, p1, p2) || Geometry::checkIntersection(enemyPos, playerPos, p2, p3) ||
            Geometry::checkIntersection(enemyPos, playerPos, p3, p4) ||Geometry::checkIntersection(enemyPos, playerPos, p4, p1)) 
        {
            return;
        }
    }
    seesPlayer = true;
}


/// <summary>
/// Отрисовка в окне
/// </summary>
/// <param name="window"></param>
void Enemy::draw(sf::RenderWindow& window) 
{
    sf::VertexArray cone(sf::PrimitiveType::TriangleFan);
    cone.append(sf::Vertex{ shape.getPosition(), sf::Color(255, 255, 0, 30) });

    float baseAngle = shape.getRotation().asDegrees();
    int segments = 30;

    for (int i = 0; i <= segments; ++i) {
        float a = (baseAngle - VIEW_ANGLE) + (VIEW_ANGLE * 2 * i / segments);
        float r = a * DEG_TO_RAD;
        sf::Vector2f end = shape.getPosition() + sf::Vector2f(std::cos(r), std::sin(r)) * VIEW_DISTANCE;
        cone.append(sf::Vertex{ end, sf::Color(255, 255, 0, 30) });
    }
    window.draw(cone);
    window.draw(shape);
}