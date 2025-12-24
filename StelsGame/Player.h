#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class Player
{
public:
	sf::CircleShape shape;

	Player();
	void update(float dt, Level& level);
	void draw(sf::RenderWindow& window);
	void reset();
};

