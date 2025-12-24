#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

struct EnemyConfig {
	std::vector<sf::Vector2f> path;
};

class Level
{
public:
	vector<sf::RectangleShape> walls;
	sf::RectangleShape goal;

	// Данные для инициализации динамических объектов (Игрока и Врагов)
	sf::Vector2f playerStartPos;
	std::vector<EnemyConfig> enemyConfigs;

	Level();

	// Метод загрузки
	bool loadFromFile(std::string& filename);

	void draw(sf::RenderWindow& window);
	bool checkCollision(sf::FloatRect bounds);
};

