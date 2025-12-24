#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class Player
{
private:
	const float RADIUS = 12.f;
public:
	sf::CircleShape shape;

	Player();
	void update(float dt, Level& level);
	void draw(sf::RenderWindow& window);
	void reset();
};

