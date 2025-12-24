#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Level
{
public:
	vector<sf::RectangleShape> walls;
	sf::RectangleShape goal;

	Level();
	void draw(sf::RenderWindow& window);
	bool checkCollisision(sf::FloatRect bounds);

private:
	void createWall(float x, float y, float w, float h);
};

