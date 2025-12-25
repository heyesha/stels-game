#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

struct EnemyConfig {
	vector<sf::Vector2f> path;
};

class Level
{
public:
	vector<sf::RectangleShape> walls;
	sf::RectangleShape goal;

	sf::Vector2f playerStartPos;
	vector<EnemyConfig> enemyConfigs;

	Level();

	bool loadFromFile(string filename);

	void draw(sf::RenderWindow& window);
	bool checkCollision(sf::FloatRect bounds);
};

