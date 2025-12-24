#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"

class Enemy {
public:
    sf::ConvexShape shape;
    std::vector<sf::Vector2f> path;
    size_t pathIndex = 0;
    bool seesPlayer = false;

    Enemy(std::vector<sf::Vector2f> p);
    
    void update(float dt);
    void checkVision(sf::Vector2f playerPos, const std::vector<sf::RectangleShape>& walls);
    void draw(sf::RenderWindow& window);
};